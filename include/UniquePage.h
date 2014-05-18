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
#include <string>
#include <utility>
#include <vector>
#include <fstream>
#include "Document.h"

class UniquePage {
public:
	UniquePage(const std::string &filename, Document &doc);
	UniquePage(Document &doc);
	void write_page(const std::string &filename);
	void compare_page(Document &doc);
	virtual ~UniquePage();
private:
	//比较两个网页内容
	int compare(const WebPage &lhs, const WebPage &ths);
};

#endif /* UNIQUEPAGE_H_ */
