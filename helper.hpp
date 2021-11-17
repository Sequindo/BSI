#include <vector>
#include <cstring>
#include <cstdlib>
#include "solver.hpp"

enum CalculatingOptions
{
    PARALLEL_REL = 0,
    SERIAL_REL = 1,
    PROPORTIONAL = 2,
    NONE_SPECIFIED = -1
};

class Helper
{
CalculatingOptions options = NONE_SPECIFIED;
float reliability = 0.0;
int numberOfUnits = 0;
std::vector<float> prod_p;
std::vector<float> nondef_p;

public:
    Helper() {}
    void printHelp(std::ostream& out)
    {
        std::string str{
            "This program solves basic probability exercises from the field of Reliability Engineering.\n"
            "Cmdline args:\n"
            "-help: show usage\n"
            "-num: specify the number of units (e.g. devices) + (unsigned int)\n"
            "-rel: specify the common reliability of units (e.g. devices) + (float from a range (0.0,1.0))\n"
            "-parallel: calculate the probability of m of n units remaining operative, based on reliability factor provided\n"
            "-proportional: calculate the probability that a fault part comes from a N plant, based on values provided.\n"
            "-prod: specify a proportion of production for a N plant. N is based on the order of the arguments + float (0.0,1.0)\n"
            "-nondef: specify a PROBABILITY OF A NON-DEFECTIVE product coming from a N plant. N is based on the order of the arguments. + float(0.0,1.0)\n"
        };
        out << str;
    }
    void parseArgCmdline(int argc, char** argv)
    {
        for(int i=1;i<argc;i++)
        {
            if(strcmp(argv[i],"-help")==0)
            {
                printHelp(std::cout);
                return;
            } //ok
            else if(strcmp(argv[i],"-parallel")==0)
            {
                options = PARALLEL_REL;
            } //ok
            else if(strcmp(argv[i],"-proportional")==0)
            {
                options = PROPORTIONAL;
            } //ok
            else if(strcmp(argv[i],"-rel")==0)
            {
                reliability = atof(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-num")==0)
            {
                numberOfUnits = atof(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-prod")==0)
            {
                prod_p.push_back(atof(argv[++i]));
            } //ok
            else if(strcmp(argv[i],"-nondef")==0)
            {
                nondef_p.push_back(atof(argv[++i]));
            } //ok
        }
        switch(options)
        {
            case(PARALLEL_REL):
                Solver::parallelSolve(numberOfUnits, reliability);
                break;
            case(PROPORTIONAL):
                Solver::proportionalSolve(prod_p, nondef_p);
                break;
            default:
                std::cout << "Something went wrong\n Maybe it will help...";
                printHelp(std::cout);
                break;
        }       
    }
};