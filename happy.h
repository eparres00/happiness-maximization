#ifndef _HAPPY_
#define _HAPPY_

#include <vector>
#include <string>

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
	*     0   1   2   3
	*   +---+---+---+---+
	* 0 | 0 | 39| 24| 12|
	*   +---+---+---+---+
	* 1 | 30|100| 78| 55|
	*   +---+---+---+---+
	* 2 | 20| 80| 68| 47|
	*   +---+---+---+---+
	* 3 | 13| 67| 45| 35|
	*   +---+---+---+---+
	*
	*/
	void prettyPrintWeights();

	/*
	* print out adjacency matrix in a clean format
	*
	*     	    evan    jorge   zach  sydney
	*         +------+-------+------+------+
	*   ryan  |      |       |   x  |      |
	*         +------+-------+------+------+
	* rachel  |      |       |   x  |      |
	*         +------+-------+------+------+
	*   will  |  x   |       |      |      |
	*         +------+-------+------+------+
	* andrew  |      |   x   |      |   x  |
	*         +------+-------+------+------+
	*
	*/
	void prettyPrintGraph();

	/*
	* read in values for weights
	*/
	void initializeWeights(std::string weight_filename);

	/*
	* read in values for graph from the files
	* requires weights to be initialized
	*/
	void initializeGraph(std::string big_filename, std::string little_filename);

	/*
	* reads in command line args, sets algorithm.
	*/
	void initializeFlags(int argc, char * argv[]);

	/*
	* read in values provided into internal data structures
	*/
	void initializeInputs(int argc, char * argv[]);

	/*
	* match bigs and littles depending on algo choice
	*/
	void match();

	/*
	* iterate through set of all edges, picking the maxmium edge
	* each iteration. once a pairing is made, remove all edges connecting
	* to those people
	*/
	void matchLocallyOptimal();

	/*
	* DP algorithm to find max of (Take, Not Take) of every edge
	*/
	void matchGloballyOptimal();

	/*
	* display matching results
	*/
	void printResults();

private:

	// adjacency matrix representing graph.
	// outer vector is littles, inner vector is bigs
	std::vector<std::vector<unsigned int>> graph;

	// table of values for certain connections
	// row index is big's ranking, column is little's ranking
	std::vector<std::vector<unsigned int>> weights;

	// names of bigs in order of the csv
	std::vector<std::string> big_names;

	// names of littles in order of the csv
	std::vector<std::string> little_names;

	// which algorithm we want to use.
	// 0 -> prioritize strong connections (local)
	// 1 -> prioritize maximum group happiness (global)
	bool algo = 0;


};

#endif