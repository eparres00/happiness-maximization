#ifndef _HAPPY_
#define _HAPPY_

#include <vector>

class Happy {

public:

	/*
	* ctor
	*/
	Happy();

	/*
	* print out command line options with descriptions
	*/
	void printHelp();

	/*
	* print out weights table in a clean format
	*/
	void prettyPrintWeights();

	/*
	* print out adjacency matrix in a clean format
	*/
	void prettyPrintGraph();

	/*
	* reads in command line args, sets algorithm.
	*/
	void getMode(int argc, char * argv[]);

private:

	// adjacency matrix representing graph.
	// outer vector is littles, inner vector is bigs
	std::vector<std::vector<int>> graph;

	// which algorithm we want to use.
	// 0 -> prioritize strong connections
	// 1 -> prioritize maximum group happiness
	bool algo = 0;


};

#endif