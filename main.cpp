#include "happy.h"


int main(int argc, char *argv[])
{
	Happy tht;

    tht.initializeInputs(argc, argv);
    tht.match();

    return 0;
}
