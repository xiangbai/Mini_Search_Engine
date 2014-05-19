/*
 * UniquePage.cpp
 *
 *  Created on: May 17, 2014
 *      Author: wang
 */

#include "UniquePage.h"
#include "WebPage.h"
#include "Document.h"
#include "Offset.h"
//需要传递一个对象的引用
/*
 * 网页去重
 */
UniquePage::UniquePage(const std::string &indexfile, Document &document, Offset &offset)
:_document(document), offset(offset)
{
	// TODO Auto-generated constructor stub
	std::cout<<"before delete size is: "<<_document.v_webpage.size() <<std::endl;
	compare_page();
	write_page(indexfile);
}
void UniquePage::write_page(const std::string &filename)
{
	std::ofstream fout ;
	fout.open(filename.c_str()) ;
	if(!fout)
	{
		perror("file open failed");
		exit(1);
	}
	/*
	 * 如何来处理不重复网页
	 */
	int count = 0 ;
	for(std::vector<WebPage>::size_type ix = 0 ; ix != _document.v_webpage.size(); ix++)
	{
		if(!(_document.v_webpage[ix].tag))  //标记为不重复页面
		{
			fout<<_document.v_webpage[ix]._docid<<"\t"<<offset.v_offset[ix+1].first<<"\t" <<offset.v_offset[ix+1].second<<std::endl;
			++count ;
		}
	}
	std::cout<<"不重复页面："<<count<<std::endl;
}
void UniquePage::compare_page()
{
	//数组中的每个对象进行比较
	int count ;
	for(std::vector<WebPage>::size_type ix = 0 ; ix != _document.v_webpage.size(); ix++)
	{
		if( _document.v_webpage[ix].tag)  //已被标记为删除网页
		{
			continue ;
		}
		for(std::vector<WebPage>::size_type iy = 0 ; iy != _document.v_webpage.size(); iy++)
		{
			if(ix != iy)  //避免自身与自身的比较
			{
				if( _document.v_webpage[iy].tag)   //标记为要删除的网页
				{
					continue ;
				}
				count = compare(_document.v_webpage[ix].top_word,  _document.v_webpage[iy].top_word);
				if(count > 6) //两个对象的交集大于6，认为是该两篇内容是相似的，需要删除其中的一篇，则删出docid较大的一篇
				{
					if( _document.v_webpage[ix]._docid >  _document.v_webpage[iy]._docid)
					{
						 _document.v_webpage[ix].tag = true ; //用与标记该网页是否是重复网页
					}
					else
					{
						 _document.v_webpage[iy].tag = true ;
					}
				}
			}

		}
	}
}
//比较两个对象中词组相等的个数
int UniquePage::compare(std::vector<std::string> &lhs, std::vector<std::string> &ths)
{
	int count = 0 ;
	std::vector<std::string>::iterator lh_iter = lhs.begin();
	while(lh_iter != lhs.end())
	{
		std::vector<std::string>::iterator th_iter = ths.begin();
		while(th_iter != ths.end())
		{
			if(*lh_iter == *th_iter)
			{
				++count ;
			}
			++th_iter ;
		}
		if(count == 7)
		{
			break;
		}
		++lh_iter ;
	}
	return count ;

}
UniquePage::~UniquePage() {
	// TODO Auto-generated destructor stub
}

