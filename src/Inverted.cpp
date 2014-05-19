/*
 * Inverted.cpp
 *
 *  Created on: May 19, 2014
 *      Author: wang
 */

#include "Inverted.h"
#include "Document.h"
#include "WebPage.h"
Inverted::Inverted(const std::string &invertedfile,Document &doc):doc(doc){
	// TODO Auto-generated constructor stub
	m_invert.clear();
	read_map_to_file(invertedfile);
}
void Inverted::read_map_to_file(const std::string &invertedfile)
{
	std::ofstream fout;
	fout.open(invertedfile.c_str());
	if(!fout)
	{
		perror("file open failed");
		exit(1);
	}
	//不含重复网页
	//关键字，文章号， 词频
//	EncodingConverter trans ;
//	std::string str ;
	for(std::vector<WebPage>::size_type ix = 0; ix != doc.v_webpage.size(); ++ix)
	{
		for(std::map<std::string, int>::iterator iter = doc.v_webpage[ix].m_word.begin(); iter != doc.v_webpage[ix].m_word.end(); ++iter)
		{
			//str = iter->first;
			//std::cout<<"str: "<<trans.gbkToutf8(str)<<std::endl;
			m_invert[iter->first].push_back(std::make_pair( doc.v_webpage[ix]._docid,iter->second));
		}
	}
	std::cout<<"m_invert size: "<<m_invert.size()<<std::endl;
	std::map<std::string, std::vector<std::pair<int, int> > >::iterator iter = m_invert.begin() ;
	while(iter != m_invert.end())
	{
		fout<<iter->first<<"   ";
		for(std::vector<std::pair<int, int> >::iterator v_iter = iter->second.begin(); v_iter != iter->second.end(); ++v_iter)
		{
			fout<<v_iter->first<<"   "<<v_iter->second<<"   ";
		}
		fout<<std::endl;
		++iter;
	}
	fout.close();
}
Inverted::~Inverted() {
	// TODO Auto-generated destructor stub
}

