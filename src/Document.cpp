/*
 * Document.cpp
 *
 *  Created on: May 16, 2014
 *      Author: wang
 */

#include "Document.h"
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include "UniquePage.h"
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define TOPN 11
using namespace CppJieba;

const char * const dict_path = "/var/www/search_engine/data/jieba.dict.gbk";
const char * const model_path = "/var/www/search_engine/data/hmm_model.gbk";

Document::Document(const std::string &webpage, const std::string &indexpage, const std::string &stopfile)
	:v_webpage(0){        //初始化列表
	// TODO Auto-generated constructor stub
	_loadStopWordDict(stopfile);
	read_page(webpage, indexpage);
}
//读取配置文件中每个网页文件
void Document::read_page(const std::string &webpage, const std::string &indexpage)
{
	FILE *p_page, *p_index ;
		p_page = fopen(webpage.c_str(), "r");  //读网页库文件
		p_index = fopen(indexpage.c_str(), "r");   //读取索引文件
		if(p_page == NULL || p_index == NULL)
		{
			perror("Error opening file");
		}
		int start_index ;
		int end_index ;
		char str[100] ;
		memset(str, 0, 100);
		std::cout<<"before the size is: "<<v_webpage.size()<<std::endl;
		while(fgets(str, 100, p_index) != NULL)   //顺序读取索引值
		{
			WebPage page ;
			sscanf(str, "%d%d%d", &page._docid, &start_index, &end_index);  //得到文档的开始和结束部分

			fseek(p_page, start_index, SEEK_SET); //定位文件指针

			char *result = new char[end_index + 1]() ;
			fgets(result, end_index + 1, p_page) ; //获取一个文档的内容

			std::string document(result) ;

			cut_page(page, document);    //分词操作
			/*
			 * 分完词之后求词频的topN，然后将其加入到vector中
			 */

			int topN = TOPN ;
			sort_page_words(page,topN);  //获取topN


			v_webpage.push_back(page) ;
		//	EncodingConverter trans;
		//	if(page._docid < 20)
		//	{
				//std::cout<<"page.m_word: "<<page.m_word.size()<<std::endl;
			/*	for(std::map<std::string, int>::iterator iter = page.m_word.begin(); iter != page.m_word.end(); ++iter)
				{
					std::string temp = iter->first;
					temp = trans.gbkToutf8(temp);

					std::cout<<temp<<"-----"<<temp.size()<<"-------"<<iter->second<<std::endl;
				}
				std::cout<<"*************"<<std::endl;  */
		//		delete [] result ;
		//		continue;
		//	}
		//	else
		//	{
		//		delete [] result ;
		//		break;
		//	}
			delete [] result ;
		}

		std::cout<<"v_webpage the size is: "<<v_webpage.size()<<std::endl;
		fclose(p_page);
		fclose(p_index);
}
//分词
void Document::cut_page(WebPage &page , std::string &document) //或得一篇文章的全部内容
{
	MixSegment segment(dict_path, model_path);
	std::vector<std::string> words ;
	words.clear() ;
	get_info(page,document);  //分别获取文档的内容

	segment.cut(page._content, words);//这个需要定位到content之后的内容,同时考虑停用词的情况
	/*
	 * 分割之后的词存储在words数组中，现在需要对它进行统计词和词频
	 * 需要注意，还需要考虑停用词的情况，去除停用词的所有新词
	 */
	//遍历分词数组，以记录每个分词的词频
	std::map<std::string, int> map_word;
	std::string space(" ");
	//char n = 13 ;
	//printf("%c\n",n);
	for(std::vector<std::string>::iterator iter = words.begin(); iter != words.end(); iter++)
	{
		if(*iter != space)
		{
			//将分割出来的单词添加到map中，并统计该词出现的词频
			pair<std::map<string, int>::iterator, bool> ret =
					map_word.insert(make_pair(*iter, 1));
			if (!ret.second)
			{
				++ret.first->second;
			}
		}
	}
	get_wordvector(page, map_word);   //去停用词，获取唯一有效的词库

}

//去除停用词的情况
void Document::get_wordvector(WebPage &page, std::map<std::string, int> & map_word)
{
	//遍历map，去出停用词，写入数组中
	for(std::map<std::string, int>::iterator iter = map_word.begin(); iter != map_word.end(); ++iter)
	{
		//分词在停用词表之中
		if(_stopWords.end() != _stopWords.find(iter->first))
		{
			map_word.erase(iter++);
			continue;
		}
		//分词不在停用词表之中
		page.m_word.insert(std::make_pair(iter->first, iter->second));  //统计词和词频
	}
}

//获取文档的相应信息
void Document::get_info(WebPage &page , std::string &document)
{
	/*int url_begin ;
	int url_end;
	url_begin = document.find("<url>");
	url_end = document.find("</url>");
	page._url = document.substr(url_begin+5, url_end-url_begin-5);

	int title_begin ;
	int title_end ;
	title_begin = document.find("<title>") ;
	title_end = document.find("</title>") ;   //获取title
	page._title= document.substr(title_begin+7, title_end-title_begin-7) ;
*/
	int content_begin ;
	int content_end;
	content_begin = document.find("<content>");
	content_end = document.find("</content>") ;
	page._content = document.substr(content_begin+9, content_end-content_begin-9) ;
}
//比较策略
bool _cmp(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs)
{
	return lhs.second > rhs.second;
}
void Document::sort_page_words(WebPage &page, int topN)
{
	topN = MIN(topN, page.m_word.size());
	std::vector<std::pair<std::string, int> > keywords ;
	keywords.clear();
	std::copy(page.m_word.begin(), page.m_word.end(), std::inserter(keywords, keywords.begin()));
	//排序获取前10个的数据
	partial_sort(keywords.begin(), keywords.begin() + topN, keywords.end(), _cmp);
	keywords.resize(topN);
	page.m_word.clear() ;
	for(std::vector<std::pair<std::string, int> >::iterator iter = keywords.begin(); iter != keywords.end() ; ++iter)
	{
		page.m_word.insert(*iter);
	}
	//std::cout<<"before size is "<<page.m_word.size()<<std::endl;
}
//加载停用词到内存中
void Document::_loadStopWordDict(const std::string &filePath)
{
	std::ifstream ifs(filePath.c_str());
	//EncodingConverter trans ;
	if(!ifs)
	{
	    perror("open file failed.");
	    assert(false);
	}
	std::string line ;
	while(getline(ifs, line))
	{
		//line = trans.utf8Togbk(line) ;  //将UTF8转换成GBK格式
	    _stopWords.insert(line);
	}
	assert(_stopWords.size());
}
Document::~Document() {
	// TODO Auto-generated destructor stub
}



int main(int argc, char **argv)
{
	Conf conf(argv[1]);
	Document doc(conf.get_value("Web_page"), conf.get_value("Index_page"), conf.get_value("Stop_list"));
	UniquePage uqpage(doc);
	std::cout<<"end"<<std::endl;
	return 0 ;
}
