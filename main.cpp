#include <iostream>
#include "helper.hpp"

int main(int argc, char** argv) 
{
    Helper helper;
    helper.parseArgCmdline(argc, argv);
    return 0;
}