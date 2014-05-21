/*
 * Inverted.cpp
 *
 *  Created on: May 19, 2014
 *      Author: wang
 */

#include "Inverted.h"
#include "Document.h"
#include "WebPage.h"
Inverted::Inverted(const std::string &invertedfile,Document &doc):doc(doc),_pageNum(0){
	// TODO Auto-generated constructor stub
	m_invert.clear();
	m_normalized.clear() ;
	m_normize.clear() ;
	Construct_inverted(invertedfile);
}
void Inverted::get_invert()
{
	std::ofstream fout ;
	fout.open("/var/www/search_engine/data/word_freq.txt") ;
	//不含重复网页
	//关键字，文章号， 词频
	for(std::vector<WebPage>::size_type ix = 0; ix != doc.v_webpage.size(); ++ix)
	{
		for(std::map<std::string, int>::iterator iter = doc.v_webpage[ix].m_word.begin(); iter != doc.v_webpage[ix].m_word.end(); ++iter)
		{
			m_invert[iter->first].push_back(std::make_pair( doc.v_webpage[ix]._docid,iter->second));
			fout<<iter->first<<'\t'<<iter->second<<std::endl;
		}
	}
	fout.close() ;
	_pageNum = doc.v_webpage.size();
	std::cout<<"m_invert size: "<<m_invert.size()<<std::endl;
}
void Inverted::Construct_inverted(const std::string &invertedfile)
{
	get_invert();    //获取关键字，文章号， 词频的形式

	/*
	 * 计算每个词在文档中的权重
	 * 归一化操作，文档中所有词的权重
	 */
	std::cout<<"count weight begin"<<std::endl;
	count_weight();  //计算权重,文档中的每个词在该文档中的权中
	std::cout<<"count weight end"<<std::endl;
	std::cout<<"normalized begin"<<std::endl;
	get_normalized(invertedfile); //归一化
	std::cout<<"normalized end"<<std::endl;

}
/*
 * 关键词在文档中的权重值
 */
void Inverted::count_weight()
{
	double weight ;
	int docNum ;
	std::pair<int, double> tmp ;
	std::map<std::string, std::vector<std::pair<int, int> > >::iterator iter = m_invert.begin() ;
	while(iter != m_invert.end())
	{
		docNum = iter->second.size() ;
		for(std::vector<std::pair<int, int> >::iterator v_iter = iter->second.begin(); v_iter != iter->second.end(); ++v_iter)
		{
			weight = v_iter->second * log(_pageNum/docNum);  //在文档中的权重
			tmp = std::make_pair(v_iter->first, weight);   //docid 权重
			m_normize[v_iter->first] += weight * weight ;   //文档中所有关键字的累加权重和
			m_normalized[iter->first].push_back(tmp) ;  //文档中的关键字在该文档中的权重
		}
		++iter ;
	}
	std::cout<<"m_normize size: "<<m_normize.size()<<std::endl;
	std::cout<<"count weight m_normalized size: "<<m_normalized.size()<<std::endl;

}
//归一化操作
void Inverted::get_normalized(const std::string &invertedfile)
{
	/*
	 * 边计算归一化边写入文件
	 */
	std::ofstream fout;
	fout.open(invertedfile.c_str());
	if(!fout)
	{
		perror("file open failed");
		exit(1);
	}
	std::map<std::string, std::vector<std::pair<int, double> > >::iterator iter = m_normalized.begin() ;
	while(iter != m_normalized.end())
	{
		fout<<iter->first<<'\t' ;  //关键词
		for(std::vector<std::pair<int, double> >::iterator v_iter = iter->second.begin(); v_iter != iter->second.end(); ++v_iter)
		{
			fout<<v_iter->first<<'\t'<<v_iter->second/sqrt(m_normize[v_iter->first]) <<'\t';
		}
		fout<<std::endl;
		++iter ;
	}
	std::cout<<"get_normalized m_normalized size: "<<m_normalized.size()<<std::endl;
	fout.close();
}
//将计算完归一化后的结果写入到文件中
void Inverted::write_to_file(const std::string &invertedfile)
{
	std::ofstream fout;
	fout.open(invertedfile.c_str());
	if(!fout)
	{
		perror("file open failed");
		exit(1);
	}
	/*
	* 将倒排索引写入到文件中
	*/
	std::map<std::string, std::vector<std::pair<int, double> > >::iterator iter = m_normalized.begin() ;
	while(iter != m_normalized.end())
	{
		fout<<iter->first<<"   ";
		for(std::vector<std::pair<int, double> >::iterator v_iter = iter->second.begin(); v_iter != iter->second.end(); ++v_iter)
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

