/*
 * UniquePage.h
 *
 *  Created on: May 17, 2014
 *      Author: wang
 */

#ifndef UNIQUEPAGE_H_
#define UNIQUEPAGE_H_
/*
 * 用与实现网页去重
 */
#include <string>
#include <utility>
class UniquePage {
public:
	UniquePage();
	virtual ~UniquePage();
private:
	static bool _cmp(const std::pair<std::string, int>& lhs, const std::pair<std::string, int>& rhs)
	{
	    return lhs.second > rhs.second;
	}
};

#endif /* UNIQUEPAGE_H_ */
