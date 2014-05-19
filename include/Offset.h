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
	virtual ~Offset();
	std::map<int, std::pair<int, int> > v_offset ;
	std::map<int, std::string> v_content ;
private:
	void _loadIndexWordDict(const std::string &webpage, const std::string &indexpage);
	void _loadContentDict(FILE *p_page, int docid, int start_index, int end_index);
};

#endif /* OFFSET_H_ */
