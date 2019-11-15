#ifndef _HAPPY_
#define _HAPPY_

#include <vector>

class Happy {

public:

	Happy();

	void printHelp(char *argv[]);

	void prettyPrintWeights();

	void prettyPrintGraph();

	unsigned int getMode(int argc, char * argv[]);

private:

	std::vector<std::vector<int>> graph;
	bool algo = 0;


};

#endif