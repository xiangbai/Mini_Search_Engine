/*
 * UniquePage.h
 *
 *  Created on: May 17, 2014
 *      Author: wang
 */

#ifndef UNIQUEPAGE_H_
#define UNIQUEPAGE_H_
/*
 * 用与实现网页去重,只要词中有六个相等的词组，则认为其是相似的，则删除其中的一篇
 */
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "WebPage.h"
class Document ;
class Offset ;
class UniquePage {
public:
	UniquePage(const std::string &indexfile, Document &_document, Offset &offset);
	void write_page(const std::string &indexfile);
	void compare_page();
	virtual ~UniquePage();
private:
	//比较两个网页内容
	int compare(std::vector<std::string> &lhs, std::vector<std::string> &ths);
	Document &_document ;
	Offset &offset ;
};

#endif /* UNIQUEPAGE_H_ */
