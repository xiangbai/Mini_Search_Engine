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
#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define TOPN 10
using namespace CppJieba;

Document::Document(Offset &offset, Segment &seg, const std::string &topfile):offset(offset), seg(seg), v_webpage(0)
{
	deal_page();
}
void Document::deal_page()
{
	for(std::map<int, std::string>::iterator iter = offset.v_content.begin(); iter != offset.v_content.end(); ++iter)
	{
		WebPage page ;
		get_info(page, iter->second); //获取content
		page._docid = iter->first ;
		seg.cut_page(page._content, page.m_word);//分词

		//构建优先级对列
		std::priority_queue<std::pair< int,std::string >, std::vector<std::pair<int, std::string > >,std::less<std::pair< int,std::string> > > queueKless;
		for(std::map<std::string, int>::iterator iter = page.m_word.begin(); iter != page.m_word.end(); ++iter)
		{
			queueKless.push(std::make_pair(iter->second, iter->first));   //去停用词之后的按词频的排序
		}
		int topN = MIN(TOPN, queueKless.size());
	//	_fout<<page._docid<<"\t";
		for(int i = 0 ; i < topN; ++i)
		{
			page.top_word.push_back(queueKless.top().second) ;   //对应的docid所对应的topn词频
		//	_fout<<queueKless.top().second<<"\t" ;
			queueKless.pop() ;
		}
	//	_fout<<std::endl;
		v_webpage.push_back(page) ;     //将排序之后的网页库加入到数组中，以备后面的网页去重使用
		if(page._docid %1000 ==0)
		{
			std::cout<<"ok"<<std::endl;
		}
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


int main(int argc, char **argv)
{
	Conf conf(argv[1]);

	std::string dict = conf.get_value("dict_path") ;
	std::string model = conf.get_value("model_path") ;
	MixSegment segment(dict.c_str(), model.c_str()) ;
	Offset offset(conf.get_value("Web_page"), conf.get_value("Index_page"));
	Segment seg(conf.get_value("Stop_list"), segment);

	Document doc(offset, seg,conf.get_value("TopN_list"));
	std::cout<<"end document"<<std::endl;
	UniquePage uqpage(conf.get_value("New_index"),doc, offset);
	std::cout<<"end unique"<<std::endl;
	return 0 ;
}
