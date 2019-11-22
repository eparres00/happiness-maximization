#include <getopt.h>
#include <iostream>
#include <string>
#include <algorithm>
#include "happy.h"

// ctor
Happy::Happy() {

}

void Happy::printHelp() {
    std::cout << "Happiness Maximization Help:";
    std::cout << "\n============================\n\n";
    std::cout << "--algorithm\t-a\t\tspecifiy algorithm to use. Options are:\n";
    std::cout << "           \t  \t\t0 -> prioritize high connections (locally optimal)\n";
    std::cout << "           \t  \t\t1 -> prioritize maximum group satisfaction (globally optimal)\n";

    std::cout << "--show-weights\t-w\t\tpretty print the weights file\n";
    std::cout << "--show-graph\t-g\t\tpretty print the graph from the input file\n";
    std::cout << "--help\t\t-h\t\tprint help output\n";

}

void Happy::prettyPrintWeights()
{
    // TODO: implement
}

void Happy::prettyPrintGraph()
{
    // TODO: implement
}

void initializeWeights(std::string weight_filename)
{
    
}

void initializeGraph(std::string big_filename, std::string little_filename)
{
    
}

// Process the command line
void Happy::initializeFlags(int argc, char * argv[])
{
    // do nothing if invalid use
    if(argc != 4)
    {
        std::cerr << "Error: invalid use\n" << std::endl;
        printHelp();
        exit(0);
    }

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

    while ((choice = getopt_long(argc, argv, "a:wgh", long_options, &option_index)) != -1)
    {

        switch (choice)
        {
        case 'h':
            printHelp();
            exit(0);

        case 'a':
            // choice 0 for first algorithm
            // choice 1 for second algorithm
            // any other input is invalid
            if (atoi(optarg) > 1)
            {
                std::cerr << "Error: invalid mode " << atoi(optarg) << std::endl;
                exit(1);
            }
            // set class algo flag
            this->algo = atoi(optarg);
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
        }
    }
}

void Happy::initializeInputs(int argc, char * argv[])
{
    // process command line flags
    this->initializeFlags(argc, argv);

    // grab filenames
    std::string weights_filename = std::string(argv[1]);
    std::string bigs_filename = std::string(argv[2]);
    std::string littles_filename = std::string(argv[3]);

    // fill in graph and weights
    this->initializeWeights(weights_filename);
    this->initializeGraph(bigs_filename, littles_filename);

}

void Happy::match()
{

    if(!algo)
    {
        matchLocallyOptimal();
    }
    else
    {
        matchGloballyOptimal(); 
    }

    printResults();

}