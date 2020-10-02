#include <iostream>
#include <sstream>

#include "cmd_processing.h"
#include "cmd_handler.h"

int main(int argc, char* argv[])
{
   std::cout << "Start... " << std::endl; 

    if (argc == 2) {

        std::stringstream convert(argv[1]);
        int bulkSize;
        if (convert >> bulkSize) {
            cmd::CmdProcessing cmdProcessing{bulkSize};
            cmdProcessing.exec();
        } else {
            std::cout << "Error. Size bulk is not integer number." << std::endl;
        }
    } else {
        std::cout << "Error. Set size bulk." << std::endl;
    }

    return 0;
}