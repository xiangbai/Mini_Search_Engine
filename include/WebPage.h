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
public:
	WebPage();
	virtual ~WebPage();
private:
	int _docid ;
	std::string _url ;
	std::string _title ;
	std::string _content ;
	std::map<std::string, int> m_word ;
};

#endif /* WEBPAGE_H_ */
