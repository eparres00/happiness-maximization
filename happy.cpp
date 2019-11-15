#include <getopt.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "happy.h"

// ctor
Happy::Happy() {

}

// Print help for the user when requested.
// argv[0] is the name of the currently executing program
void Happy::printHelp(char *argv[]) {
	// TODO: implement
    std::cout << "Happiness Maximization Help:";
    std::cout << "\n============================\n\n";
    std::cout << "--algorithm\t-a\t\tspecifiy algorithm to use. Options are 0\n";
    std::cout << "           \t  \t\tfor prioritizing high connections (locally optimal) and 1 for\n";
    std::cout << "           \t  \t\tprioritizing maximum group satisfaction (globally optimal)\n";

    std::cout << "--show-weights\t-w\t\tpretty print the weights file\n";
    std::cout << "--show-graph\t-g\t\tpretty print the graph from the input file\n";
    std::cout << "--help\t\t-h\t\tprint help output\n";

} // printHelp()

void Happy::prettyPrintWeights() {
    // TODO: implement
} // prettyPrintWeights()

void Happy::prettyPrintGraph() {
    // TODO: implement
} // prettyPrintGraph()

// Process the command line
unsigned int Happy::getMode(int argc, char * argv[]) {
    unsigned int algo = 0;

    // These are used with getopt_long()
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
		{ "algorithm",      required_argument, nullptr, 'a' },
		{ "show-weights",   no_argument,       nullptr, 'w' },
		{ "show-graph",     no_argument,       nullptr, 'g' },
		{ "help",           no_argument,       nullptr, 'h' },
        { nullptr,          0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "a:wgh", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            printHelp(argv);
            exit(0);

        case 'a':
            algo = atoi(optarg);
            // choice 0 for first algorithm
            // choice 1 for second algorithm
            // any other input is invalid
            if (algo > 1) {
                std::cerr << "Error: invalid mode " << algo << std::endl;
                exit(1);
            } // if
            break;

        case 'w':
            prettyPrintWeights();
            break;
        
        case 'g':
            prettyPrintGraph();
            break;

        default:
            std::cerr << "Error: invalid option" << std::endl;
            exit(1);
        } // switch
    } // while

    return algo;
} // getMode()
