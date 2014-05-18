/*
 * WebPage.h
 *
 *  Created on: May 16, 2014
 *      Author: wang
 */

#ifndef WEBPAGE_H_
#define WEBPAGE_H_

#include <string>
#include <vector>
#include <utility>
#include <map>
class WebPage {
friend class Document ;
friend class UniquePage ;
public:
	WebPage();
	virtual ~WebPage();
	//friend bool operator == (const WebPage &lhs, const WebPage &ths) ;
	//friend bool operator != (const WebPage &lhs, const WebPage &ths) ;
private:
	bool tag ;    //用于标记该网页是否是重复页面
	int _docid ;
	std::string _url ;
	std::string _title ;
	std::string _content ;
	std::map<std::string, int> m_word ;   //记录词和词频
};
#endif /* WEBPAGE_H_ */
