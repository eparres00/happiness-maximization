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
	
	
	struct HeapEntry {
		double weight;
		unsigned int big_idx;
		unsigned int little_idx;
	};

	/*
	* functor used for heap in locally optimal algo
	* { {big_name, little_name} , weight }
	*/
	struct HeapEntryCompLess
	{
		bool operator()(const HeapEntry &lhs, const HeapEntry &rhs)
		{
			return lhs.weight < rhs.weight;
		}
	};

}

#endif
