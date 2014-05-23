/*
 * ClientDeal.h
 *
 *  Created on: May 21, 2014
 *      Author: wang
 */

#ifndef CLIENTDEAL_H_
#define CLIENTDEAL_H_
#include <string>
#include <map>
#include <utility>
#include <vector>
class Segment;
class ClientDeal{
friend class Query ;
public:
	ClientDeal(Segment &seg, std::string &query);
	void count_weight();
	void display();
	virtual ~ClientDeal();
private:
	Segment &seg ;
	std::map<std::string, std::pair<int, double> > m_word; //词，频率，归一化
	std::map<std::string, int> m_seg ;  //记录词和词频
};

#endif /* CLIENTDEAL_H_ */
