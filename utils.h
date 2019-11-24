#ifndef _UTILS_
#define _UTILS_

#include <vector>
#include <string>

namespace utils {

	/*
	* splits string by delimeter and puts all items in vector
	*/
	std::vector<std::string> splitByDelimiter(std::string str, char delimiter);

	/*
	* prints a value centered given the number of total spaces allowed
	*/
	void printValCentered(double val, unsigned int total_spaces);
}

#endif
