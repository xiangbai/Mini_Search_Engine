/*
 * Segment.cpp
 *
 *  Created on: May 18, 2014
 *      Author: wang
 */

#include "Segment.h"
const char * const dict_path = "/var/www/search_engine/data/jieba.dict.gbk";
const char * const model_path = "/var/www/search_engine/data/hmm_model.gbk";

using namespace CppJieba;

Segment::Segment(const std::string &filePath) {
	// TODO Auto-generated constructor stub
	_stopWords.clear() ;
	_loadStopWordDict(filePath);  //加载停用词表
}
//分词
void Segment::cut_page(std::string &content, std::map<std::string, int> &map_word) //或得一篇文章的全部内容
{
	MixSegment segment(dict_path, model_path);

	std::vector<std::string> words ;
	words.clear() ;

	segment.cut(content, words);//这个需要定位到content之后的内容,同时考虑停用词的情况
	/*
	 * 分割之后的词存储在words数组中，现在需要对它进行统计词和词频
	 * 需要注意，还需要考虑停用词的情况，去除停用词的所有新词
	 */
	//遍历分词数组，以记录每个分词的词频
	std::string table(1, '\r');  //去除tab键
	//用于统计词和词频
	for(std::vector<std::string>::iterator iter = words.begin(); iter != words.end(); iter++)
	{
		if(*iter != " " && *iter != table && extract(*iter))
		{
			//将分割出来的单词添加到map中，并统计该词出现的词频
			pair<std::map<string, int>::iterator, bool> ret =
					map_word.insert(make_pair(*iter, 1));
			if (!ret.second)
			{
				++ret.first->second;
			}
		}
	}
}
//去停用词
bool Segment::extract(const std::string &stopword)
{
	//_stopWords.count(*iter) == 0  不再停用词中，  0是false
	return _stopWords.count(stopword) == 0;
}
//加载停用词到内存中，停用词是GBK格式文件
void Segment::_loadStopWordDict(const std::string &filePath)
{
	std::ifstream ifs(filePath.c_str());
	if(!ifs)
	{
	    perror("open file failed.");
	    assert(false);
	}
	std::string line ;
	while(getline(ifs, line))
	{
	    _stopWords.insert(line);
	}
	assert(_stopWords.size());
}
Segment::~Segment() {
	// TODO Auto-generated destructor stub
}

