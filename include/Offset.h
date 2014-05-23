/*
 * Offset.h
 *
 *  Created on: May 19, 2014
 *      Author: wang
 */

#ifndef OFFSET_H_
#define OFFSET_H_
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <fstream>
#include <stdlib.h>
class Offset {
public:
	Offset(const std::string &webpage, const std::string &indexpage);
	Offset(const std::string &invertfile);
	void _init_page(const std::string &webpage, const std::string &indexpage);
	std::string &get_content(int docid);
	virtual ~Offset();
	std::map<int, std::pair<int, int> > v_offset ;  //索引文件内容
	std::map<int, std::string> v_content ;   //网页文件内容
	std::map<std::string, std::vector<std::pair<int, int> > > m_invert ;   //倒排索引文件
private:
	void _loadIndexWordDict(const std::string &webpage, const std::string &indexpage);
	void _loadContentDict(FILE *p_page, int docid, int start_index, int end_index);
	void _loadInvertedDict(const std::string &invertfile);
};

#endif /* OFFSET_H_ */
