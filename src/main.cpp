#include <iostream>
#include "cmd_processing.h"

int main(int argc, char* argv[])
{
    CmdProcessing cmdProcessing{static_cast<int>(argv[0])};
    cmdProcessing.exec();

    return 0;
}