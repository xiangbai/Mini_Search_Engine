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
class Document {
friend class UniquePage ;
public:
	Document(const std::string &webpage, const std::string &indexpage, const std::string &stopfile);
	virtual ~Document();
	void read_page(const std::string &webpage, const std::string &indexpage);
	void get_info(WebPage &page , std::string &document);  //获取网页的content内容
	void display(int docid, WebPage &page);
private:

	std::vector<WebPage> v_webpage ;
	std::string _stopfile ;
	std::priority_queue<std::pair< int,std::string >, std::vector<std::pair<int, std::string > >,std::less<std::pair< int,std::string> > > queueKless;

	void sort_page_words(std::map<std::string, int> &m_word, int topN);  //排序，获取TOPN的词
	void one_page_info(const std::string &str, FILE *p_page, FILE*p_index);

};

#endif /* DOCUMENT_H_ */
