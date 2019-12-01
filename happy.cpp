#include <getopt.h>
#include <iostream>
#include <fstream>
#include <map>
#include <cassert>
#include <queue>
#include <set>
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
    std::cout << "\nWeights\n=======\n\n";
    // TODO: print top indexes
    std::cout << "\n";

    // print all vals
    for(unsigned int i = 0; i < weights.size(); ++i)
    {
        std::cout << "  +-----+-----+-----+-----+\n";
        std::cout << i << " |"; // print size index
        for(unsigned int j = 0; j < weights[i].size(); ++j)
        {
            utils::printValCentered(weights[i][j], 5);
            std::cout << "|";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
}

void Happy::prettyPrintGraph()
{
    // title and names
    std::cout << "\nGraph\n=======\n\n";
    // TODO: print little names
    std::cout << "\n";

    std::string horz_line = "  +-----+";
    for(unsigned int i = 0; i < graph[0].size(); ++i) {
        horz_line += "-----+";
    }
    horz_line += "\n";

    for(unsigned int i = 0; i < graph.size(); ++i)
    {
        std::cout << horz_line;
        std::cout << big_name_vec[i] << " |"; // TODO: justify big names
        for(unsigned int j = 0; j < graph[i].size(); ++j)
        {
            utils::printValCentered(graph[i][j], 5);
            std::cout << "|";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

}

void Happy::initializeWeights(std::string weight_filename)
{
    std::cout << "initializing weights...\n";

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
    std::cout << "initializing name maps...\n";

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
        big_name_vec.emplace_back(big_name);
    }

    // LITTLES
    std::ifstream little_stream(little_filename);
    line_num = 0;
    while(std::getline(little_stream, line, '\n'))
    {
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        std::string little_name = split_line[0];
        little_names[little_name] = line_num++;
        little_name_vec.emplace_back(little_name);
    }

    // big and little name maps should be filled!
}

void Happy::initializeGraph(std::string big_filename, std::string little_filename)
{
    /* 
    *   Overview: 
    *       store intermediate data of list of {big, little} name pairs
    *       to {big_rank, little_rank} pair. use info to fill in graph
    *
    *       big_rank = what the big ranked the little
    *       little_rank = what the little ranked the big
    */

    std::cout << "initializing graph...\n";

    // GRAPH SIZE INITIALIZATION
    // =========================
    // allocate num_bigs rows in graph
    graph.resize(big_names.size());
    // allocate num_littles cols in graph. initialize val to 0
    for(auto& col : graph) { col.resize(little_names.size(), 0); }
    // =========================

    // NAME PAIR MAP
    // {big, little} -> {big_rank, little_rank}
    // ===================
    std::map<std::pair<std::string, std::string>, std::pair<unsigned int, unsigned int>> name_pair_map;

    // BIGS
    std::ifstream big_stream(big_filename);
    std::string line;
    // read in big file line by line
    while(std::getline(big_stream, line, '\n'))
    {
        // split the line up by commas
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        // fill map of name -> list of names
        std::string big_name = split_line[0];
        // TODO: insert into edges set here??
        for(unsigned int i = 1; i < split_line.size(); i++)
        {
            // mark the pair {big, little} as {big_rank, 0}
            // (little rank will be filled in later)
            std::string little_name = split_line[i];
            name_pair_map[{big_name, little_name}] = {i, 0};
        }

    }

    // LITTLES
    std::ifstream little_stream(little_filename);
    // read in big file line by line
    while(std::getline(little_stream, line, '\n'))
    {
        // split the line up by commas
        std::vector<std::string> split_line = utils::splitByDelimiter(line, ',');
        // fill map of name -> list of names
        std::string little_name = split_line[0];
        // TODO: insert into edges set here??
        for(unsigned int i = 1; i < split_line.size(); i++)
        {
            // mark the pair {big, little} as having little rank i
            std::string big_name = split_line[i];
            name_pair_map[{big_name, little_name}].second = i;
        }

    }

    // FILL GRAPH
    for(auto& entry : name_pair_map)
    {
        //  0       first            second
        //  1  {first, second} -> {first, second}
        std::string big_name = entry.first.first;
        std::string little_name = entry.first.second;

        assert(big_names.find(big_name) != big_names.end());
        assert(little_names.find(little_name) != little_names.end());

        // used for indexing graph
        unsigned int big_graph_idx = big_names[big_name];
        unsigned int little_graph_idx = little_names[little_name];
        // grab the rank each person gave each other
        unsigned int big_rank = entry.second.first;
        unsigned int little_rank = entry.second.second;

        // get the weight associated with the rankings given
        double weight = weights[big_rank][little_rank];

        // set the graph at {big, little} to have apprpriate edge weight
        graph[big_graph_idx][little_graph_idx] = weight;
    }

    // graph should be full now!

}

// Process the command line
void Happy::initializeFlags(int argc, char *argv[])
{
    // do nothing if invalid use

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
        this->first_file_idx++;

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
                std::cerr << "Error: invalid algo " << atoi(optarg) << "\n";
                exit(1);
            }
            // set class algo flag
            this->algo = atoi(optarg);
            this->first_file_idx++;
            break;

        case 'w':
            this->print_weights = true;
            break;

        case 'g':
            this->print_graph = true;
            break;

        default:
            std::cerr << "Error: invalid option\n";
            exit(1);
        }
    }
}

void Happy::initializeInputs(int argc, char *argv[])
{

    // process command line flags
    this->initializeFlags(argc, argv);

    // grab filenames
    std::string weights_filename = std::string(argv[first_file_idx]);
    std::string bigs_filename = std::string(argv[first_file_idx + 1]);
    std::string littles_filename = std::string(argv[first_file_idx + 2]);

    // fill in graph and weights
    this->initializeWeights(weights_filename);
    this->initializeNames(bigs_filename, littles_filename);
    this->initializeGraph(bigs_filename, littles_filename);

    if(this->print_weights) { prettyPrintWeights(); }
    if(this->print_graph) { prettyPrintGraph(); }
}

void Happy::matchRandom()
{

}

void Happy::matchLocallyOptimal()
{
    std::set<unsigned int> bigs_taken;
    std::set<unsigned int> littles_taken;
    std::priority_queue<utils::HeapEntry, std::vector<utils::HeapEntry>, utils::HeapEntryCompLess> heap;

    std::cout << "here";

    // insert all edges
    for(unsigned int i = 0; i < graph.size(); ++i)
    {
        for(unsigned int j = 0; j < graph[0].size(); ++j)
        {
            // insert the pair of
            // { {big_idx, little_idx,}, weight }
            heap.push({weights[i][j], i, j});
        }
    }

    // repeat until all littles have been matched
    std::cout << "little name vec size: " << little_name_vec.size();
    while (littles_taken.size() != little_name_vec.size())
    {
        // take from top of heap
        utils::HeapEntry entry = heap.top();
        heap.pop();

        bool big_matched = bigs_taken.find(entry.big_idx) != bigs_taken.end();
        bool little_matched = littles_taken.find(entry.little_idx) != littles_taken.end();

        // skip this edge if either the big or little has been matched
        if(big_matched || little_matched)
            continue;

        std::string big_name = big_name_vec[entry.big_idx];      
        std::string little_name = little_name_vec[entry.little_idx];

        // mark the edge as 'taken'
        results[{big_name, little_name}] = entry.weight;
        bigs_taken.insert(entry.big_idx);
        littles_taken.insert(entry.little_idx);
    }

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
    // for(auto& entry : results)
    // {
    //     std::cout << "big name: " << entry.first.first << "\n";
    //     std::cout << "little name: " << entry.first.second << "\n";
    //     std::cout << "weight: " << entry.second << "\n";
    // }
}