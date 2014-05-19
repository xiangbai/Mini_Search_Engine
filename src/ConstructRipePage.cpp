/*
 * ConstructRipePage.cpp
 *
 *  Created on: May 15, 2014
 *      Author: wang
 */

#include "ConstructRipePage.h"
#include "EncodingConverter.h"
#include <fstream>
#include <iostream>
ConstructRipePage::ConstructRipePage(const std::string &source, const std::string &destinate, const std::string &indexfile)
	:t_pageid(1), t_index(0), start_index(0), end_index(-1) {
	// TODO Auto-generated constructor stub
	_fout.open(destinate.c_str());   //打开ripepaeg.lib文件
	if(!_fout)
	{
		throw std::runtime_error("open file failed");
	}
	_fout_index.open(indexfile.c_str());    //打开索引文件
	if(!_fout_index)
	{
		throw std::runtime_error("open file failed");
	}
	reverse_dir(source);
	//create_webpage(source);
}
//用于打开文件
std::ifstream &open_file(std::ifstream &stream, const std::string &filename)
{
	stream.clear();
	stream.close();
	stream.open(filename.c_str());
	return stream ;
}
std::string get_title(std::string line)
{
	EncodingConverter trans ;
	std::string utf_title_1("标题");
	std::string utf_title_2("标 题");
	std::string utf_kuohao("】");
	std::string gbk_title_1 = trans.utf8Togbk(utf_title_1) ;    //将utf8的“标题”转换成gbk的“标题”
	std::string gbk_title_2 = trans.utf8Togbk(utf_title_2) ;
	std::string gbk_kuohao = trans.utf8Togbk(utf_kuohao);
	int index ;
	std::string title ;
	unsigned found ;
	//寻找“标题”在文中的下标
	if((index = line.find(gbk_title_1)) != std::string::npos || (index = line.find(gbk_title_2)) !=std::string::npos)
	{
		found= line.find_last_of(gbk_kuohao);
		title = line.substr(found+1) ;
	}
	else
	{
		title = " " ;
	}
	return title ;
}

//添加一个文件的内容
void ConstructRipePage::create_webpage(const std::string &source)
{
	std::string form_1("<doc><docid>");
	std::string form_2("</docid><url>");
	std::string form_3("</url><title>");
	std::string form_4("</title><content>");
	std::string form_5("</content></doc>");

	std::ifstream fin ;
	open_file(fin, source);
	if(!fin)
	{
		throw std::runtime_error("open file failed");
	}

	std::string line ;  //按行读取文件
	std::string title ;
	int count_line = 0 ;
	start_index = _fout.tellp();

	_fout<<form_1<<t_pageid<<form_2<<"www.baidu.com"<<form_3 ;


	while(getline(fin, line) && count_line < 10)  //按行读取前10行内容，获取标题
	{
		/*
		 * 从读出的内容中解析出标题和内容
		 */
		title = get_title(line);
		if(title == " ") //得到标题的内容
		{
			++count_line ;
		}
		else
		{
			break;
		}
	}
	/*
	 * 没有标题字体的情况，获取第一行内容作为标题
	 */
	fin.seekg(0);
	if(title == " ")
	{
		while(getline(fin, line))
		{
			if(line.size() == 0)
			{
				continue ;
			}
			else
			{
				title = line ;
				_fout<<title<<form_4 ;
				break;
			}
		}
	}
	fin.seekg(0);
	while(getline(fin, line))
	{
		_fout<<line;
	}
	_fout<<form_5<<'\n';
	//测试
	end_index = _fout.tellp();
	// 最后的偏移量；
	_fout_index <<t_pageid<<"\t"<<start_index<<"\t"<<end_index-start_index <<std::endl;
	t_pageid++ ;
	fin.close();
}
//遍历目录,获取源文件
void ConstructRipePage::reverse_dir(const std::string &source)
{
	std::cout<<"reverse_dir"<<std::endl;
	DIR *pDir ;
	struct dirent *pDirent ;
	struct stat my_stat ;
	pDir = opendir(source.c_str());
	chdir(source.c_str());
	if(pDir == NULL)
	{
	     std::cout<<"dir open failed"<<std::endl;
	     exit(-1);
	}
	while((pDirent = readdir(pDir))!=NULL)
	{
	    stat(pDirent->d_name , &my_stat);
	    if(S_ISDIR(my_stat.st_mode))  //是目录的情况
	    {
	    	if(strncmp(".", pDirent->d_name, 1) == 0 || strncmp("..", pDirent->d_name, 2) == 0)
	    	{
	    		continue ;
	    	}
	    	reverse_dir(pDirent->d_name);     //继续遍历目录
	    }
	    else
	    {
	    	create_webpage(pDirent->d_name);     //只读一个文档的记录
	    /*	end_index = _fout.tellp();
	    	  // 最后的偏移量；
	    	_fout_index <<t_pageid<<"\t"<<start_index<<"\t"<<end_index-start_index <<std::endl;
	    	t_pageid++ ; */

	    }
	 }
	chdir("..");
	closedir(pDir);
}
ConstructRipePage::~ConstructRipePage() {
	// TODO Auto-generated destructor stub
	_fout.close();
	_fout_index.close();
}

int main(int argc, char **argv)
{
	std::string source = "/var/www/search_engine/data/webpage/";
	//std::string source = "/var/www/search_engine/data/C29-Transport004.txt" ;
	std::string dest = "/var/www/search_engine/data/ripepage.lib" ;
	std::string indexfile = "/var/www/search_engine/data/indexpage.txt" ;
	ConstructRipePage page(source, dest, indexfile);
	FILE *fp ;
	return 0 ;
}

