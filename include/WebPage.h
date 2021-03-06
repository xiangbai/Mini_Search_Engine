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
friend class Inverted ;
public:
	WebPage();
	virtual ~WebPage();
private:
	bool tag ;    //用于标记该网页是否是重复页面
	int _docid ;
	std::string _url ;
	std::string _title ;
	std::string _content ;
	std::map<std::string, int> m_word ;   //记录词和词频
	std::vector<std::string> top_word ;   //记录top k的词
};
#endif /* WEBPAGE_H_ */
