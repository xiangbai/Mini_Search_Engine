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
#include <math.h>
/*
 * 倒排索引类
 * 关键字 docid 归一化值
 */
class Document ;
class Inverted {
public:
	Inverted(const std::string &invertedfile,Document &doc);  //存储倒排索引中的内容
	virtual ~Inverted();
	void Construct_inverted(const std::string &invertedfile);
private:
	/*
	 * 如何解析出这样的关联数组
	 */
	std::map<std::string, std::vector<std::pair<int, int> > >m_invert ;  //关键词，文章编号，词频
	std::map<std::string, std::vector<std::pair<int, double> > >m_normalized ;  //关键词，文章编号，归一化结果
	std::map<int, double> m_normize ;
	Document &doc;
	int _pageNum ;    //网页数目
	void get_invert();
	void write_to_file(const std::string &invertedfile);
	void count_weight();   //计算权重
	void get_normalized(const std::string &invertedfile);  //归一化并写入文件中
};

#endif /* INVERTED_H_ */
