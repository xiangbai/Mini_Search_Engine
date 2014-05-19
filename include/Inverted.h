/*
 * Inverted.h
 *
 *  Created on: May 19, 2014
 *      Author: wang
 */
/*
 * 建立倒排索引表
 */
#ifndef INVERTED_H_
#define INVERTED_H_
#include <string>
#include <fstream>
#include <map>
#include <utility>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
class Document ;
class Inverted {
public:
	Inverted(const std::string &invertedfile,Document &doc);  //存储倒排索引中的内容
	virtual ~Inverted();
	void read_map_to_file(const std::string &invertedfile);
private:
	/*
	 * 如何解析出这样的关联数组
	 */
	std::map<std::string, std::vector<std::pair<int, int> > >m_invert ;  //关键词，文章编号，词频
	Document &doc;
};

#endif /* INVERTED_H_ */
