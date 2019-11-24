#include <iostream>
#include <iomanip>
#include <algorithm>
#include <cassert>
#include "utils.h"

std::vector<std::string> utils::splitByDelimiter(const std::string str, char delimiter)
{
	std::vector<std::string> split_string;
	std::vector<unsigned int> indexes;

	// keep track of all places to avoid
	for(unsigned int i = 0; i < str.length(); ++i)
	{
		if(str[i] == delimiter) { indexes.push_back(i); }
	}
	indexes.push_back(str.length());

	// fill results with everything besides delimeters
	unsigned int end_idx = 0, begin_idx = 0, len = 0;
	for(unsigned int i = 0; i < indexes.size(); i++)
	{
		end_idx = indexes[i];
		// how long to make the substring after begin_idx
		len = end_idx - begin_idx;
		// insert the substring into the results vector.
		// don't make a copy every time with emplace
		split_string.emplace_back(str.substr(begin_idx, len));
		begin_idx = end_idx + 2; // +1 since substr is inclusive on begin, +1 more for ignoring space

		// assert no newlines are in names
		assert(split_string.back().find_first_of("\n") == std::string::npos);
	}

	// make sure we copied the right number of things
	assert(split_string.size() == indexes.size());

	return split_string;
}

void utils::printValCentered(double val, unsigned int total_spaces)
{

	// num spaces used by value
	// TODO: always <total_spaces> for some reason??? need to make the number of digits in number
	unsigned int str_length = std::min((unsigned int) std::to_string(val).length(), total_spaces);
	unsigned int avail_spaces = total_spaces - str_length;
    // spaces to print after
	unsigned int num_trail_spaces = avail_spaces / 2;
	// spaces to print before. if total spaces isnt even, give more to lead
	unsigned int num_lead_spaces = avail_spaces - num_trail_spaces;

	// lead spaces
	for(unsigned int i = 0; i < num_lead_spaces; ++i) { std::cout << " "; }

	// print out max 5 digits of a floating point num
    std::cout << std::setprecision(total_spaces);
	// value
	std::cout << val;

	// trail spaces
	for(unsigned int i = 0; i < num_trail_spaces; ++i) { std::cout << " "; }
}
