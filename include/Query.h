/*
 * Query.h
 *
 *  Created on: May 20, 2014
 *      Author: wang
 */

#ifndef QUERY_H_
#define QUERY_H_
#include <string>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <sstream>
#include <utility>
#include <set>
#include <map>
#include <hash_map>
#include <vector>
#include <stdexcept>

namespace __gnu_cxx {
template<> struct hash<std::string> {
	std::size_t operator()(const std::string &s) const {
		hash<const char *> h;
		return h(s.c_str());
	}
};
}
class ClientDeal ;
class Query {
public:
	Query(ClientDeal &client, const std::string &invertedfile);
	void read_to_hash_map(const std::string &invertedfile);  //将倒排索引读入到内存中
	void write_to_file(const std::string &filename);
	void get_query_map(ClientDeal &client);//在倒排索引中搜索所有包含搜锁分词中的内容集合
	void run_query(ClientDeal &client);
	virtual ~Query();
private:
	ClientDeal &client;
	__gnu_cxx ::hash_map<std::string, std::vector<std::pair<int, double> >, __gnu_cxx ::hash<std::string> > hash_search;
	__gnu_cxx ::hash_map<std::string, std::vector<std::pair<int, double> >, __gnu_cxx ::hash<std::string> > hash_query;
	typedef __gnu_cxx ::hash_map<std::string, std::vector<std::pair<int, double> >, __gnu_cxx ::hash<std::string> >::iterator hash_search_iter ;
		typedef __gnu_cxx ::hash_map<std::string, std::vector<std::pair<int, double> >, __gnu_cxx ::hash<std::string> >::const_iterator hash_search_iter_const ;
};

#endif /* QUERY_H_ */
