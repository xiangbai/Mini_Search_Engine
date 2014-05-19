/*
 * ConstructRipePage.h
 *
 *  Created on: May 15, 2014
 *      Author: wang
 */

#ifndef CONSTRUCTRIPEPAGE_H_
#define CONSTRUCTRIPEPAGE_H_

#include <string>
#include <stdexcept>
#include <fstream>
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
class ConstructRipePage {
public:
	ConstructRipePage(const std::string &source, const std::string &destinate, const std::string &indexfile);

	void create_webpage(const std::string &source);   //创建网页库
	void reverse_dir(const std::string &source);
	virtual ~ConstructRipePage();
private:
	int t_pageid ;
	int t_index ;
	int start_index ;
	int end_index ;
	std::ofstream _fout ;        //网页文件流
	std::ofstream _fout_index ;  //索引文件流
};

#endif /* CONSTRUCTRIPEPAGE_H_ */
