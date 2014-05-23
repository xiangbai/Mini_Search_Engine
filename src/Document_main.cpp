/*
 * Document_main.cpp
 *
 *  Created on: May 21, 2014
 *      Author: wang
 */
#include "Document.h"
#include "Conf.h"
#include "Segment.h"
#include "Offset.h"
#include "Inverted.h"
using namespace CppJieba;

int main(int argc, char **argv)
{
	Conf conf(argv[1]);

	std::string dict = conf.get_value("dict_path") ;
	std::string model = conf.get_value("model_path") ;
	MixSegment segment(dict.c_str(), model.c_str()) ;
	//Offset offset(conf.get_value("Web_page"), conf.get_value("Index_page"));
	Segment seg(conf.get_value("Stop_list"), segment);

	//Document doc(offset, seg);
	//doc.deal_page();

	Offset n_offset(conf.get_value("Web_page"), conf.get_value("New_index"));
	n_offset._init_page(conf.get_value("Web_page"), conf.get_value("New_index")) ;

	Document n_doc(n_offset, seg);
	n_doc.deal_page();
	std::cout<<"end document"<<std::endl;
	Inverted invert(conf.get_value("Inverted_index"),n_doc);
	std::cout<<"end ivert"<<std::endl;
	//UniquePage uqpage(conf.get_value("New_index"),doc, offset);   //网页去重
	//std::cout<<"end unique"<<std::endl;
	return 0 ;
}


