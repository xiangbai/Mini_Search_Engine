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
#include "Segment.h"

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define TOPN 10
using namespace CppJieba;

Document::Document(const std::string &webpage, const std::string &indexpage, const std::string &stopfile)
	:v_webpage(0), _stopfile(stopfile){        //初始化列表
	// TODO Auto-generated constructor stub
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
		one_page_info(str, p_page, p_index);
	}

	std::cout<<"v_webpage the size is: "<<v_webpage.size()<<std::endl;
	fclose(p_page);
	fclose(p_index);
}
void Document::one_page_info(const std::string &str, FILE *p_page, FILE*p_index)
{
	int start_index ;
	int end_index ;
	WebPage page ;
	sscanf(str.c_str(), "%d%d%d", &page._docid, &start_index, &end_index);  //得到文档的开始和结束部分
	fseek(p_page, start_index, SEEK_SET); //定位文件指针

	char *result = new char[end_index + 1]() ;
	fgets(result, end_index + 1, p_page) ; //获取一个文档的内容

	std::string document(result) ;
	get_info(page,document);  //分别获取文档的content内容

	Segment seg(_stopfile);
	seg.cut_page(page._content, page.m_word);

	//构建优先级对列
	for(std::map<std::string, int>::iterator iter = page.m_word.begin(); iter != page.m_word.end(); ++iter)
	{
		queueKless.push(std::make_pair(iter->second, iter->first));   //去停用词之后的按词频的排序
	}
	/*
	* 分完词之后求词频的topN，然后将其加入到vector中
	*/
	sort_page_words(page.top_word,TOPN);  //获取词和词频的topN
	/*
	* 可以使用优先级队列来进行排序，对map对象中的元素按照词频进行排序
	* 需要考虑所要使用的排序函数，如优先级队列
	*/
	v_webpage.push_back(page) ;     //将排序之后的网页库加入到数组中，以备后面的网页去重使用
	delete [] result ;
	std::cout<<"over page "<<page._docid<<std::endl;
}

void Document::display(int docid, WebPage &page)
{
	EncodingConverter trans;
	if(page._docid < 20)
	{
		std::cout<<"page.m_word: "<<page.m_word.size()<<std::endl;
		std::cout<<"page.top_word: "<<page.top_word.size()<<std::endl;
		for(std::map<std::string, int>::iterator iter = page.top_word.begin(); iter != page.top_word.end(); ++iter)
		{
			std::string temp = iter->first;
			temp = trans.gbkToutf8(temp);
			std::cout<<temp<<"-------"<<iter->second<<std::endl;
		}
		std::cout<<"*************"<<std::endl;
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

//使用优先级队列，以获取TOPN的词组
void Document::sort_page_words(std::map<std::string, int> &top_word, int topN)
{
	topN = MIN(topN, queueKless.size());
	 pair<int,string>tmp;
	for(int i = 0 ; i < topN; ++i)
	{
		tmp = queueKless.top() ;
		top_word.insert(std::make_pair(tmp.second, tmp.first)) ;
		queueKless.pop() ;
	}
}
Document::~Document() {
	// TODO Auto-generated destructor stub
}


int main(int argc, char **argv)
{
	Conf conf(argv[1]);
	Document doc(conf.get_value("Web_page"), conf.get_value("Index_page"), conf.get_value("Stop_list"));
	//UniquePage uqpage(doc);
	std::cout<<"end"<<std::endl;
	return 0 ;
}
