/*
 * UniquePage.cpp
 *
 *  Created on: May 17, 2014
 *      Author: wang
 */

#include "UniquePage.h"
#include "WebPage.h"
//需要传递一个对象的引用
UniquePage::UniquePage(const std::string &filename, Document &doc):v_count(0){
	// TODO Auto-generated constructor stub

}
UniquePage::UniquePage(Document &doc):v_count(0){
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
	//std::vector<std::pair<std::string, int> >::iterator iter =doc.v_webpage.begin();
	//while(iter != doc.v_webpage.end())
	//{

	//	++iter ;
	//}
	//数组中的每个对象进行比较
	int count ;
	for(std::vector<WebPage>::size_type ix = 0 ; ix != doc.v_webpage.size(); ix++)
	{
		for(std::vector<WebPage>::size_type iy = 0 ; iy != doc.v_webpage.size(); iy++)
		{
			if(ix != iy)  //避免自身与自身的比较
			{
				count = compare(doc.v_webpage[ix], doc.v_webpage[iy]);
				if(count > 6) //两个对象的交集大于6，认为是该两篇内容是相似的，需要删除其中的一篇，则删出docid较大的一篇
				{
					int docid  ;      //= MAX(doc.v_webpage[ix]._docid, doc.v_webpage[iy]._docid);
					if(doc.v_webpage[ix]._docid > doc.v_webpage[iy]._docid)
					{
						docid = ix ;
					}
					else
					{
						docid = iy ;
					}
					//v_count.push_back(docid);  //记录要删除网页的docid
					delete_similar_page(doc.v_webpage, docid);
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
void swap(WebPage &lhs, WebPage &ths)
{
	WebPage temp ;
	temp = lhs;
	lhs = ths ;
	ths = temp ;
}
void UniquePage::delete_similar_page(std::vector<WebPage> &webpage,int docid)
{
	/*
	 * 将要删除的与最后一个进行交换，然后直接pop就可以了
	 */
	std::vector<WebPage>::iterator iter = webpage.end() ;
	--iter ;   //指向最后一个元素
	swap(*iter, webpage[docid]) ;
	webpage.pop_back() ;  //去除最后一个元素
}
UniquePage::~UniquePage() {
	// TODO Auto-generated destructor stub
}

