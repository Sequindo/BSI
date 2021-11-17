#include <vector>
#include <cstring>
#include <cstdlib>
#include "solver.hpp"

enum CalculatingOptions
{
    PARALLEL_REL = 0,
    SERIAL_REL = 1,
    NONE_SPECIFIED = -1
};

class Helper
{
CalculatingOptions options = NONE_SPECIFIED;
float reliability = 0.0;
int numberOfUnits = 0;

public:
    Helper() {}
    void printHelp(std::ostream& out)
    {
        std::string str{
            "This program solves basic probability exercises from the field of Reliability Engineering.\n"
            "Cmdline args:\n"
            "-h, --help: show usage\n"
            "-n, --num: specify the number of units (e.g. devices) + (unsigned int)\n"
            "-p, --parallel: calculate the probability of m of n units remaining operative, based on reliability factor provided\n"
            "-r, --reliability: specify the reliability factor + (float)\n"
        };
        out << str;
    }
    void parseArgCmdline(int argc, char** argv)
    {
        for(int i=1;i<argc;i++)
        {
            if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0)
            {
                printHelp(std::cout);
                return;
            }
            else if(strcmp(argv[i],"-p")==0 || strcmp(argv[i],"--parallel")==0)
            {
                options = PARALLEL_REL;
            }
            else if(strcmp(argv[i],"-r")==0 || strcmp(argv[i],"--reliability")==0)
            {
                reliability = atof(argv[++i]);
            }
            else if(strcmp(argv[i],"-n")==0 || strcmp(argv[i],"--num")==0)
            {
                numberOfUnits = atof(argv[++i]);
            }
        }
        switch(options)
        {
            case(PARALLEL_REL):
                Solver::parallelSolve(numberOfUnits, reliability);
                break;
            default:
                std::cout << "Something went wrong\n Maybe it will help...";
                printHelp(std::cout);
                break;
        }       
    }
};