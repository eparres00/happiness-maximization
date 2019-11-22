#include "happy.h"


int main(int argc, char *argv[])
{
	Happy tht;

    tht.initializeInputs(argc, argv);
    tht.match();
    tht.printResults();

    return 0;
}
