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
	void cut_page(WebPage &page , std::string &document);
	void get_info(WebPage &page , std::string &document);
	void get_wordvector(WebPage &page, std::map<std::string, int> & map_word);
private:

	std::vector<WebPage> v_webpage ;

	std::set<std::string> _stopWords ;  //存储形式是GBK格式
	void _loadStopWordDict(const std::string &filePath);

	void sort_page_words(WebPage &page, int topN);

};

#endif /* DOCUMENT_H_ */
