/*
 * UniquePage.cpp
 *
 *  Created on: May 17, 2014
 *      Author: wang
 */

#include "UniquePage.h"
#include "WebPage.h"
//需要传递一个对象的引用
/*
 * 网页去重
 */
UniquePage::UniquePage(const std::string &filename, Document &doc){
	// TODO Auto-generated constructor stub

}
UniquePage::UniquePage(Document &doc){
	// TODO Auto-generated constructor stub
	std::cout<<"before delete size is: "<<doc.v_webpage.size() <<std::endl;
	compare_page(doc);
	std::cout<<"after delete size is: "<<doc.v_webpage.size() <<std::endl;
}
void UniquePage::write_page(const std::string &filename)
{
}
void UniquePage::compare_page(Document &doc)
{
	//数组中的每个对象进行比较
	int count ;
	for(std::vector<WebPage>::size_type ix = 0 ; ix != doc.v_webpage.size(); ix++)
	{
		if(doc.v_webpage[ix].tag)
		{
			continue ;
		}
		for(std::vector<WebPage>::size_type iy = 0 ; iy != doc.v_webpage.size(); iy++)
		{
			if(ix != iy)  //避免自身与自身的比较
			{
				if(doc.v_webpage[iy].tag)   //标记为要删除的网页
				{
					continue ;
				}
				count = compare(doc.v_webpage[ix], doc.v_webpage[iy]);
				if(count > 6) //两个对象的交集大于6，认为是该两篇内容是相似的，需要删除其中的一篇，则删出docid较大的一篇
				{
					if(doc.v_webpage[ix]._docid > doc.v_webpage[iy]._docid)
					{
						doc.v_webpage[ix].tag = true ; //用与标记该网页是否是重复网页
					}
					else
					{
						doc.v_webpage[iy].tag = true ;
					}
				}
			}

		}
	}
}
//比较两个对象中词组相等的个数
int UniquePage::compare(const WebPage &lhs, const WebPage &ths)
{
	int count = 0 ;
	std::map<std::string, int>::const_iterator lh_iter = lhs.m_word.begin();
	while(lh_iter != lhs.m_word.end())
	{
		std::map<std::string, int>::const_iterator th_iter = ths.m_word.begin();
		while(th_iter != ths.m_word.end())
		{
			if(lh_iter->first == th_iter->first)
			{
				++count ;
			}
			++th_iter ;
		}
		++lh_iter ;
	}
	return count-1 ;

}
UniquePage::~UniquePage() {
	// TODO Auto-generated destructor stub
}

