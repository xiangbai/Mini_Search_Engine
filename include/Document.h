/*
 * Document.h
 *
 *  Created on: May 16, 2014
 *      Author: wang
 */

#ifndef DOCUMENT_H_
#define DOCUMENT_H_

#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <cstdio>
#include <stdexcept>
#include <utility>
#include <vector>
#include <map>
#include <set>
#include <assert.h>
#include <cmath>
#include <queue>

#include "MixSegment.hpp"
#include "EncodingConverter.h"
#include "WebPage.h"
#include "Conf.h"

/*
 * Document是为每一个网页进行分词操作
 */
class Offset;
class Segment;
class Document {
friend class UniquePage ;
public:
	//Document(const std::string &webpage, const std::string &indexpage, const std::string &stopfile);
	Document(Offset &offset, Segment &seg, const std::string &topfile);
	virtual ~Document();
	void get_info(WebPage &page , std::string &document);  //获取网页的content内容
	void display(int docid, WebPage &page);
	void deal_page();
	void write_top_word();
private:
	Offset &offset ;
	Segment &seg ;
	std::vector<WebPage> v_webpage ;
	std::ofstream _fout;

};

#endif /* DOCUMENT_H_ */
