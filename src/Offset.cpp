/*
 * Offset.cpp
 *
 *  Created on: May 19, 2014
 *      Author: wang
 */

#include "Offset.h"
#include "Conf.h"
#include <string.h>
/*
 * 将索引内容读入到内存中
 * 加载网页内容到内存中
 */
Offset::Offset(const std::string &webpage, const std::string &indexpage) {
	// TODO Auto-generated constructor stub
	v_offset.clear() ;
	v_content.clear() ;
	m_invert.clear();
	//_loadIndexWordDict(webpage, indexpage);   //加载索引文件到内存中
}
Offset::Offset(const std::string &invertfile)
{
	v_offset.clear() ;
	v_content.clear() ;
	m_invert.clear();
	_loadInvertedDict(invertfile);
}
void Offset::_init_page(const std::string &webpage, const std::string &indexpage)
{
	_loadIndexWordDict(webpage, indexpage);
}
/*
 * 加载倒排索引到内存中
 */
void Offset::_loadInvertedDict(const std::string &invertfile)
{
	std::ifstream fin;
	fin.open(invertfile.c_str()) ;
	if(!fin)
	{
		perror("Error opening file");
	}
	std::string line ;
	/*while(getline(fin, line))
	{

	}*/
	fin.close();
}
/*
 * 加载索引文件到内存中
 */
void Offset::_loadIndexWordDict(const std::string &webpage, const std::string &indexpage)
{
	std::ifstream fin;
	fin.open(indexpage.c_str()) ;
	if(!fin)
	{
		perror("Error opening file");
	}
	FILE *p_page;
	p_page = fopen(webpage.c_str(), "r");  //读网页库文件
	if(p_page == NULL)
	{
		perror("Error opening file");
	}
	std::string str ;
	int startIndex;
	int endIndex ;
	int docid ;
	while(getline(fin, str))  //读取一行的内容
	{
		sscanf(str.c_str(), "%d%d%d", &docid, &startIndex, &endIndex);
		v_offset.insert(std::make_pair(docid, std::make_pair(startIndex,endIndex)));
		_loadContentDict(p_page,docid, startIndex,endIndex);
		str.clear() ;
	}
	fin.close();
	fclose(p_page);
	std::cout<<"index size is: "<<v_offset.size()<<std::endl;
	std::cout<<"content size is: "<<v_content.size()<<std::endl;
}
/*
 * 加载页面内容到内存中
 */
void Offset::_loadContentDict(FILE *p_page, int docid, int start_index, int end_index)
{
	fseek(p_page, start_index, SEEK_SET); //定位文件指针
	char *result = new char[end_index + 1]() ;
	fgets(result, end_index + 1, p_page) ; //获取一个文档的内容
	v_content.insert(std::make_pair(docid, result)) ;
}
std::string &Offset::get_content(int docid)
{

	int content_begin ;
	int content_end;
	content_begin = v_content[docid].find("<content>");
	content_end = v_content[docid]("</content>") ;
	std::string _content = v_content[docid].substr(content_begin+9, content_end-content_begin-9) ;
	return v_content[docid] ;
}
Offset::~Offset() {
	// TODO Auto-generated destructor stub
}
/*
int main(int argc, char **argv)
{
	Conf conf(argv[1]);
	Offset offset(conf.get_value("Web_page"), conf.get_value("Index_page"));
	return 0 ;
}
*/
