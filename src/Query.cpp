/*
 * Query.cpp
 *
 *  Created on: May 20, 2014
 *      Author: wang
 */

#include "Query.h"
/*
 * 读取倒排索引到内存中，进行相似度计算
 */
Query::Query(ClientDeal &client, const std::string &invertedfile):client(client) {
	// TODO Auto-generated constructor stub
	hash_search.clear();
	hash_query.clear() ;
	read_to_hash_map(invertedfile); //将倒排索引表中的数据读入到内存中
}
void Query::read_to_hash_map(const std::string &invertedfile)
{
	std::ifstream fin ;
	fin.open(invertedfile.c_str());
	if(!fin)
	{
		perror("file open failed");
		exit(1);
	}
	std::string line ;
	int count = 0 ;
	std::string word ;
	std::pair<int, double> tmp ;
	int docid ;
	double inverted ;
	while(getline(fin,line))  //每次读取一行内容
	{
		std::istringstream sin(line);
		sin>>word ;
		while(sin>>docid>>inverted)
		{
			tmp = std::make_pair(docid, inverted);
			hash_search[word].push_back(tmp);
		}
		sin.clear();
	}
	std::cout<<"size is: "<<hash_search.size()<<std::endl;
}
void Query::run_query(ClientDeal &client)
{
	get_query_map(client);
	/*
	 * 求交集
	 */
}
//从倒排索引中获取包含搜索词中的所有集合
void Query::get_query_map(ClientDeal &client)
{
	//GBK存储形式
	std::pair<int, double> tmp ;
	std::string str ;
	for(std::map<std::string, std::pair<int, double> >::iterator iter = client.m_word.begin(); iter != client.m_word.end(); ++iter)
	{
		str = iter->first;
		hash_search_iter_const iter = hash_search.find(str);
		if(iter != hash_search.end())  //在hash中找到搜索词所对应的查询结果
		{
			for(std::vector<std::pair<int, double> >::iterator v_iter = hash_search[str].begin();v_iter != hash_search[str].end(); ++v_iter)
			{
				tmp = std::make_pair(v_iter->first, v_iter->second);
				hash_query[str].push_back(tmp);
			}
		}
	}
}
Query::~Query() {
	// TODO Auto-generated destructor stub
}
void Query::write_to_file(const std::string &filename)
{
	std::ofstream fout ;
	fout.open(filename.c_str()) ;
	hash_search_iter iter =  hash_search.begin() ;
	while(iter != hash_search.end())  //将hash_map写入到文件中
	{
		fout<<iter->first<<"   ";
		for(std::vector<std::pair<int, double> >::iterator v_iter = iter->second.begin(); v_iter != iter->second.end(); ++v_iter)
		{
			fout<<v_iter->first<<"   "<<v_iter->second<<"   ";
		}
		fout<<std::endl;
		++iter ;
	}
}
/*
int main(int argc, char **argv)
{
	std::string filename = "/var/www/search_engine/data/inverted_index.dat";
	std::string file = "/var/www/search_engine/data/inverted_test.dat" ;
	Query query(filename);
	//query.write_to_file(file);
	return 0 ;
}
*/
