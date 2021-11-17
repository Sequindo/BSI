#include <vector>
#include <cstring>
#include <cstdlib>
#include "solver.hpp"

enum CalculatingOptions
{
    PARALLEL_REL = 0,
    SERIAL_REL = 1,
    PROPORTIONAL = 2,
    CARD_DECK = 3,
    FAILURE_PROB = 4,
    NONE_SPECIFIED = -1
};

class Helper
{
CalculatingOptions options = NONE_SPECIFIED;
float reliability = 0.0;
int numberOfUnits = 0;
long ftime = 0;
int failures_number = 0;
int operating_hrs = 0;
std::vector<float> prod_p;
std::vector<float> nondef_p;
std::vector<float> probs;

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
            "-deck: calculate the probability using deck of cards\n"
            "-failure: calculate the probability of a failure for a single device, given rest of parameters.\n"
            "-proportional: calculate the probability that a fault part comes from a N plant, based on values provided.\n"
            "-prod: specify a proportion of production for a N plant. N is based on the order of the arguments + float (0.0,1.0)\n"
            "-nondef: specify a PROBABILITY OF A NON-DEFECTIVE product coming from a N plant. N is based on the order of the arguments. + float(0.0,1.0)\n"
            "-operating_t: specify a real operating time of a device in HOURS. + (int)\n"
            "-fnum: specify a numer of failures to calculate a random failure rate. + (int)\n"
            "-ftime: specify a time interval to calculate a random failure rate in SECONDS. + (long)\n"
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
            else if(strcmp(argv[i],"-deck")==0)
            {
                options = CARD_DECK;
            } //ok
            else if(strcmp(argv[i],"-rel")==0)
            {
                reliability = atof(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-num")==0)
            {
                numberOfUnits = atoi(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-prod")==0)
            {
                prod_p.push_back(atof(argv[++i]));
            } //ok
            else if(strcmp(argv[i],"-nondef")==0)
            {
                nondef_p.push_back(atof(argv[++i]));
            } //ok
            else if(strcmp(argv[i],"-operating_t")==0)
            {
                operating_hrs = atoi(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-failure")==0)
            {
                options = FAILURE_PROB;
            } //ok
            else if(strcmp(argv[i],"-fnum")==0)
            {
                failures_number = atoi(argv[++i]);
            } //ok
            else if(strcmp(argv[i],"-ftime")==0)
            {
                ftime = atoi(argv[++i]);
            } //ok
        }
        try {
            switch(options)
            {
                case(PARALLEL_REL):
                    Solver::parallelSolve(numberOfUnits, reliability);
                    break;
                case(PROPORTIONAL):
                    Solver::proportionalSolve(prod_p, nondef_p);
                    break;
                case(CARD_DECK):
                    Solver::cardDeckSolver();
                    break;
                case(FAILURE_PROB):
                    Solver::failureProbSolver(failures_number, ftime, operating_hrs);
                    break;
                default:
                    std::cout << "Something went wrong\n Maybe it will help...\n";
                    printHelp(std::cout);
                    break;
            }
        } catch(std::string& e){
            std::cout << e << std::endl;
        }    
    }
};