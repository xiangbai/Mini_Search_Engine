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
#include "Offset.h"
#include "Segment.h"
#include "MixSegment.hpp"
#include "Inverted.h"
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define TOPN 10
using namespace CppJieba;
/*
 * 文档处理类，主要函数的作用是：
 *对网页库中的数据进行分词
 *统计topk，以去除重复网页
 */

Document::Document(Offset &offset, Segment &seg):offset(offset), seg(seg), v_webpage(0)
{

}
//分词操作
void Document::deal_page()
{
	for(std::map<int, std::string>::iterator iter = offset.v_content.begin(); iter != offset.v_content.end(); ++iter)
	{
		WebPage page ;
		get_info(page, iter->second); //获取content
		page._docid = iter->first ;
		seg.cut_page(page._content, page.m_word);//分词结果已读入内存中,已经知道相应网页中的词和词频

		//get_top_word(page);  //获取topN
		v_webpage.push_back(page) ;     //将排序之后的网页库加入到数组中，以备后面的网页去重使用
		if(page._docid %1000 ==0)
		{
			std::cout<<"ok"<<std::endl;
		}
	}
	std::cout<<"v_webpage size: "<<v_webpage.size()<<std::endl;
}
//获取topN
void Document::get_top_word(WebPage &page)
{
	//构建优先级对列
	std::priority_queue<std::pair< int,std::string >, std::vector<std::pair<int, std::string > >,std::less<std::pair< int,std::string> > > queueKless;
	for(std::map<std::string, int>::iterator iter = page.m_word.begin(); iter != page.m_word.end(); ++iter)
	{
		queueKless.push(std::make_pair(iter->second, iter->first));   //去停用词之后的按词频的排序
	}
	int topN = MIN(TOPN, queueKless.size());
	for(int i = 0 ; i < topN; ++i)
	{
		page.top_word.push_back(queueKless.top().second) ;   //对应的docid所对应的topn词频
		queueKless.pop() ;
	}
	v_webpage.push_back(page) ;     //将排序之后的网页库加入到数组中，以备后面的网页去重使用
	if(page._docid %1000 ==0)
	{
		std::cout<<"ok"<<std::endl;
	}
}
void Document::display(int docid, WebPage &page)
{
	EncodingConverter trans;
	if(page._docid < 20)
	{
		std::cout<<"page.m_word: "<<page.m_word.size()<<std::endl;
		std::cout<<"page.top_word: "<<page.top_word.size()<<std::endl;
		for(std::vector<std::string>::iterator iter = page.top_word.begin(); iter != page.top_word.end(); ++iter)
		{
			std::string temp = *iter;
			temp = trans.gbkToutf8(temp);
			std::cout<<temp<<"---"<<std::endl;
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


Document::~Document() {
	// TODO Auto-generated destructor stub
}


