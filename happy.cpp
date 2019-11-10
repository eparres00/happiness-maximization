#include <getopt.h>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;


// Print help for the user when requested.
// argv[0] is the name of the currently executing program
void printHelp(char *argv[]) {
	//TODO: implement
} // printHelp()


// Process the command line
string getMode(int argc, char * argv[]) {
    bool modeSpecified = false;
    string mode;

    // These are used with getopt_long()
    opterr = true; // Give us help with errors
    int choice;
    int option_index = 0;
    option long_options[] = {
        // TODO: Fill in two lines, for the "mode" ('m') and
        // the "help" ('h') options.
		{ "mode",  required_argument, nullptr, 'm' },
		{ "help",  no_argument,       nullptr, 'h' },
        { nullptr, 0,                 nullptr, '\0' }
    };

    // TODO: Fill in the double quotes, to match the mode and help options.
    while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
        switch (choice) {
        case 'h':
            printHelp(argv);
            exit(0);

        case 'm':
            mode = optarg;
            if (mode != "resize" && mode != "reserve" && mode != "nosize") {
                cerr << "Error: invalid mode " << mode << endl;
                exit(1);
            } // if
            modeSpecified = true;
            break;

        default:
            cerr << "Error: invalid option" << endl;
            exit(1);
        } // switch
    } // while

    if (!modeSpecified) {
        cerr << "Error: no mode specified" << endl;
        exit(1);
    } // if

    return mode;
} // getMode()


// This function is already done.
int main(int argc, char *argv[]) {
    string mode;

    mode = getMode(argc, argv);

    return 0;
} // main()
