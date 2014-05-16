/*
 * Conf.h
 *
 *  Created on: May 4, 2014
 *      Author: wang
 */

#ifndef CONF_H_
#define CONF_H_

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdexcept>
#include <string>
#include <map>
class Conf {
public:
	Conf(const std::string &dir);
	const std::string get_value(const std::string &key)const;
	virtual ~Conf();
private:
	std::ifstream fin ;
	std::map<std::string, std::string> m_read;
};

#endif /* CONF_H_ */
