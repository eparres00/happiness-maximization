#include <getopt.h>
#include <iostream>
#include <fstream>
#include "happy.h"
#include "utils.h"

// ctor
Happy::Happy() {}

void Happy::printHelp()
{
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

    // title and indexes
    std::cout << "Weights\n=======\n\n";
    // TODO: print top indexes
    std::cout << "\n";

    // print all vals
    for(int i = 0; i < weights.size(); ++i)
    {
        std::cout << "  +-----+-----+-----+-----+\n";
        std::cout << i << " |"; // print size index
        for(int j = 0; j < weights[i].size(); ++j)
        {
            utils::printValCentered(weights[i][j], 5);
            std::cout << "|";
        }
        std::cout << std::endl;
    }
}

void Happy::prettyPrintGraph()
{
    // TODO: implement
}

void Happy::initializeWeights(std::string weight_filename)
{
    std::ifstream sstream(weight_filename);
    std::string line;

    // read in weights file line by line
    while(std::getline(sstream, line, '\n'))
    {
        // will hold all vals for this row
        std::vector<double> row;
        // split the line up by commas
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        // fill row with integer values of the split string
        for(std::string& entry : split_line) { row.push_back(stod(entry)); }

        // insert the entire row into weights
        weights.emplace_back(row);
    }

    // weights should be full now!!
}

void Happy::initializeNames(std::string big_filename, std::string little_filename)
{
    // BIGS
    std::ifstream big_stream(big_filename);
    std::string line;
    unsigned int line_num = 0;
    while(std::getline(big_stream, line, '\n'))
    {
        // split the line up by commas
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        // grab big name and insert into map
        std::string big_name = split_line[0];
        big_names[big_name] = line_num++;
    }

    // LITTLEs
    std::ifstream little_stream(little_filename);
    line_num = 0;
    while(std::getline(little_stream, line, '\n'))
    {
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        std::string little_name = split_line[0];
        little_names[little_name] = line_num++;
    }

    // maps should be filled!
}

void Happy::initializeGraph(std::string big_filename, std::string little_filename)
{
    
}

// Process the command line
void Happy::initializeFlags(int argc, char *argv[])
{
    // do nothing if invalid use
    // if (argc != 4)
    // {
    //     std::cerr << "Error: invalid use\n" << std::endl;
    //     printHelp();
    //     exit(1);
    // }

    // These are used with getopt_long()
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
        {"algorithm", required_argument, nullptr, 'a'},
        {"show-weights", no_argument, nullptr, 'w'},
        {"show-graph", no_argument, nullptr, 'g'},
        {"help", no_argument, nullptr, 'h'},
        {nullptr, 0, nullptr, '\0'}};

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
                std::cerr << "Error: invalid algo " << atoi(optarg) << std::endl;
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

void Happy::initializeInputs(int argc, char *argv[])
{
    // grab filenames
    std::string weights_filename = std::string(argv[1]);
    std::string bigs_filename = std::string(argv[2]);
    std::string littles_filename = std::string(argv[3]);

    // fill in graph and weights
    this->initializeWeights(weights_filename);
    this->initializeNames(bigs_filename, littles_filename);
    this->initializeGraph(bigs_filename, littles_filename);

    // process command line flags
    this->initializeFlags(argc, argv);
}

void Happy::matchLocallyOptimal()
{
}

void Happy::matchGloballyOptimal()
{
}

void Happy::match()
{

    if (!algo)
    {
        matchLocallyOptimal();
    }
    else
    {
        matchGloballyOptimal();
    }
}

void Happy::printResults()
{
}