/*
 * Conf.cpp
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#include "Conf.h"
#include "ConstructRipePage.h"
#include "ConstructRipePage.h"
Conf::Conf(const std::string &dir){
	fin.open(dir.c_str()) ;
	if(!fin)
	{
		perror("file open error");
		exit(-1);
	}
	std::string key , value;
	while(fin >> key >> value)   //打开配置文件，读取里面相应的文件信息
	{
		m_read.insert(make_pair(key, value));
	}
	//服务器一启动就打开配置文件
	//ConstructRipePage page(get_value("Source_page"), get_value("Web_page"), get_value("Index_page"));
}

//通过相应的名字获取地址
const std::string Conf::get_value(const std::string &key)const
{
	std::map<std::string, std::string>::const_iterator it = m_read.find(key);
	if(it == m_read.end())
	{
		throw std::runtime_error("error read configure file");
	}

	return it->second;
}
Conf::~Conf() {
	// TODO Auto-generated destructor stub
	fin.close() ;
}

