/*
 * ClientDeal.cpp
 *
 *  Created on: May 21, 2014
 *      Author: wang
 */

#include "ClientDeal.h"
#include "EncodingConverter.h"
#include "Segment.h"
#include "Conf.h"
#include <cmath>
#include <iostream>
/*
 * 将客户的查询词进行分词
 * 统计词频，和归一化的结果
 */
using namespace CppJieba;
ClientDeal::ClientDeal(Segment &seg, std::string &query):seg(seg) {
	// TODO Auto-generated constructor stub
	std::cout<<query<<std::endl;
	m_word.clear() ;
	m_seg.clear() ;
	EncodingConverter trans ;
	query = trans.utf8Togbk(query);
	seg.cut_page(query, m_seg); //分词，统计词和词频
	count_weight();
}
void ClientDeal::count_weight()
{
	double weight ;
	double all_weight = 0.0 ;
	std::pair<int, double>temp ;
	for(std::map<std::string, int>::iterator iter = m_seg.begin(); iter != m_seg.end(); ++iter)
	{
		weight = iter->second * (log(1/1)+0.05);
		temp = std::make_pair(iter->second, weight);
		m_word.insert(std::make_pair(iter->first, temp));
		all_weight += weight ;
	}
	for(std::map<std::string, int>::iterator iter = m_seg.begin(); iter != m_seg.end(); ++iter)
	{
		m_word[iter->first].second = m_word[iter->first].second/sqrt(all_weight); //归一化结果
	}
}
void ClientDeal::display()
{
	EncodingConverter trans ;
	for(std::map<std::string, std::pair<int, double> >::iterator iter = m_word.begin(); iter != m_word.end(); ++iter)
	{
		std::string str = iter->first ;
		std::cout<<trans.gbkToutf8(str)<<"  "<<iter->second.first<<"  "<<iter->second.second<<std::endl;
	}
}
ClientDeal::~ClientDeal() {
	// TODO Auto-generated destructor stub
}
int main(int argc, char **argv)
{
	Conf conf(argv[1]);

	std::string dict = conf.get_value("dict_path") ;
	std::string model = conf.get_value("model_path") ;
	MixSegment segment(dict.c_str(), model.c_str()) ;
	Segment seg(conf.get_value("Stop_list"), segment);
	std::string query("北京大学举行云计算大会");
	ClientDeal client(seg, query);
	client.display();
	return 0 ;
}
