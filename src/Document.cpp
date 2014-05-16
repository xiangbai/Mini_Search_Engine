/*
 * Document.cpp
 *
 *  Created on: May 16, 2014
 *      Author: wang
 */

#include "Document.h"
using namespace CppJieba;

const char * const dict_path = "/var/www/search_engine/data/jieba.dict.gbk";
const char * const model_path = "/var/www/search_engine/data/hmm_model.gbk";

Document::Document(const std::string &webpage, const std::string &indexpage, const std::string &stopfile)
	:v_webpage(0){        //初始化列表
	// TODO Auto-generated constructor stub
	_loadStopWordDict(stopfile);
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
		WebPage page ;
		char str[100] ;
		memset(str, 0, 100);
		while(fgets(str, 100, p_index) != NULL)   //顺序读取索引值
		{
			sscanf(str, "%d%d%d", &page._docid, &start_index, &end_index);  //得到文档的开始和结束部分

			fseek(p_page, start_index, SEEK_SET); //定位文件指针

			char *result = new char[end_index + 1]() ;
			fgets(result, end_index + 1, p_page) ; //获取一个文档的内容

			std::string document(result) ;
			cut_page(page, document);

			delete [] result ;
		}
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

	for(std::vector<std::string>::iterator iter = words.begin(); iter != words.end(); iter++)
	{
		//将分割出来的单词添加到map中，并统计该词出现的词频
		std::pair<std::map<string, size_t>::iterator, bool> ret =
				map_word.insert(make_pair(*iter, 1));
		if (!ret.second)
		{
			 ++ret.first->second;
		}
	}
	get_wordvector(page, map_word);

}
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
		page.v_word.push_back(std::pair<std::string, int>(iter->first, iter->second));
	}
}

//获取文档的相应信息
void Document::get_info(WebPage &page , std::string &document)
{
	int url_begin ;
	int url_end;
	url_begin = document.find("<url>");
	url_end = document.find("</url>");
	page._url = document.substr(url_begin+5, url_end);

	int title_begin ;
	int title_end ;
	title_begin = document.find("<title>") ;
	title_end = document.find("</title>") ;   //获取title
	page._title= document.substr(title_begin+7, title_end) ;

	int content_begin ;
	int content_end;
	content_begin = document.find("<content>");
	content_end = document.find("</content>") ;
	page._content = document.substr(content_begin+9, content_end) ;
}

void Document::_loadStopWordDict(const std::string &filePath)
{
	std::ifstream ifs(filePath.c_str());
	EncodingConverter trans ;
	if(!ifs)
	{
	    perror("open file failed.");
	    assert(false);
	}
	std::string line ;
	while(getline(ifs, line))
	{
		line = trans.utf8Togbk(line) ;  //将UTF8转换成GBK格式
	    _stopWords.insert(line);
	}
	assert(_stopWords.size());
}
Document::~Document() {
	// TODO Auto-generated destructor stub
}

int main(int argc, char **argv)
{
	return 0 ;
}
