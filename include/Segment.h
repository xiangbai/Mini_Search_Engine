/*
 * Segment.h
 *
 *  Created on: May 18, 2014
 *      Author: wang
 */

#ifndef SEGMENT_H_
#define SEGMENT_H_
#include <string>
#include <utility>
#include <vector>
#include <set>
#include <map>
#include "MixSegment.hpp"
class Segment {
public:
	Segment(const std::string &filePath);
	virtual ~Segment();
	void cut_page(std::string &content, std::map<std::string, int> &map_word);  //进行分词操作
	bool extract(const std::string &stopword);

private:
	std::set<std::string> _stopWords ;  //存储形式是GBK格式
	void _loadStopWordDict(const std::string &filePath);  //加载停用词文件
};

#endif /* SEGMENT_H_ */
