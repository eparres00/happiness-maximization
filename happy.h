#ifndef _HAPPY_
#define _HAPPY_

#include <vector>
#include <string>
#include <unordered_map>

class Happy {

public:

	/*
	* ctor
	*/
	Happy();

	/*
	* read in values provided into internal data structures
	*/
	void initializeInputs(int argc, char * argv[]);

	/*
	* match bigs and littles depending on algo choice
	*/
	void match();

	/*
	* display matching results
	*/
	void printResults();

private:

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
	*   ryan  |   x  |       |   x  |      |
	*         +------+-------+------+------+
	* rachel  |      |       |   x  |   x  |
	*         +------+-------+------+------+
	*   will  |  x   |   X   |      |      |
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
	* make map of big and little names to index in the file.
	* used for graph initialization
	*/
	void initializeNames(std::string big_filename, std::string little_filename);

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
	* randomly match pairs. used for benchmarking
	*/
	void matchRandom();

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

	// adjacency matrix representing graph.
	// outer vector is littles, inner vector is bigs
	std::vector<std::vector<double>> graph;

	// table of values for certain connections
	// row index is big's ranking, column is little's ranking
	std::vector<std::vector<double>> weights;

	// names of bigs corresponding to index in graph.
	// index is the order in which they were specified in the csv file.
	// store vector of inx -> name for printing ease
	std::unordered_map<std::string, unsigned int> big_names;
	std::vector<std::string> big_name_vec;

	// names of littles corresponding to index in graph.
	// index is the order in which they were specified in the csv file.
	// store vector of inx -> name for printing ease
	std::unordered_map<std::string, unsigned int> little_names;
	std::vector<std::string> little_name_vec;

	// must keep track of flags since it changes the 
	// position of the filenames in argv array
	unsigned int first_file_idx = 1;

	// which algorithm we want to use.
	// 0 -> prioritize strong connections (local)
	// 1 -> prioritize maximum group happiness (global)
	bool algo = false;
	bool print_weights = false;
	bool print_graph = false;

};

#endif