#include <iostream>

class Solver {

public:
    static void proportionalSolve(std::vector<float>& prod_p, std::vector<float>& nondef_p)
    {
        if(prod_p.size()!=nondef_p.size())
            throw std::string("Both vectors must be the same size.\n");
        if(prod_p.empty() || nondef_p.empty())
            throw std::string("Both vectors must contain at least 1 element.\n");
        //auto sum_control = [&](std::vector<float>vec){float sum=0; for(auto& a : vec) sum = sum + a; return sum;};
        //if(sum_control(prod_p)<99.0 || sum_control(prod_p) > 101.0)
            //throw std::string("For both vectors sum of the elements must be 100.0!\n");
        std::cout << "The proportions of production of " << prod_p.size() << " plants: ";
        for(auto& a : prod_p)
        {
            std::cout << a << " ";
        }
        std::cout << std::endl;
        std::cout << "The probabilities of non-defective product coming from " << prod_p.size() << " plants: ";
        for(auto& a : nondef_p)
        {
            std::cout << a << " ";
        }
        std::cout << std::endl;
        float den = 0.0;
        for(int i=0;i<prod_p.size();i++)
        {
            den = den + prod_p.at(i)*(1.0 - nondef_p.at(i));
        }
        auto probability = [&](int i) -> float{
            return (prod_p[i]*(1.0-nondef_p[i]))/den;
        };
        for(int i=0;i<prod_p.size();i++)
        {
            std::cout << "The probability that the fault part comes from plant " << i+1 << " equals: ";
            std::cout << probability(i)*100 << "%" << std::endl;
        }       
    }

    static void parallelSolve(int num, float rel)
    {
        auto probability_calc = [=](std::ostream& os, int it) -> std::ostream& {

            auto res = static_cast<float>(binomial(num,num-it));
            for(int j=0;j<it;j++)
                res = res * rel;
            for(int j=0;j<num-it;j++)
                res = res * (1.0-rel);
            os << res;
            return os;
        };
        std::cout << "Common reliability rate is " << rel << ". Therefore common failure rate is " << 1.0 - rel << "." << std::endl;
        for(int i=0;i<=num;i++)
        {
            std::cout << "Probability that " << i << " out of " << num << " units will remain operative: ";
            probability_calc(std::cout, i) << std::endl;
        }
    }

    static void cardDeckSolver()
    {
        float allCards = 52, typeOfCards;
        auto probability = [](float typeOfCards, float allCards) -> float {
            return (typeOfCards / allCards) * 100;
        };
        std::cout << "Insert which card do you want to check: " << std::endl;
        std::cout << "1 - diamond, 2 - black, 3 - nine" << std::endl;

        int choice;
        std::cin >> choice;

        switch(choice) {
            case 1:
            typeOfCards = 13;
            break;

            case 2: 
            typeOfCards = 26;
            break;

            case 3:
            typeOfCards = 4;
            break;
 
            default:
            std::cout << "Wrong input. " << std::endl;
            break;
        }
        std::cout << "Probability that a card chosen by you is on the top of the deck equals: " << probability(typeOfCards,allCards)<< " %" << std::endl;
        return;
    }

    static void failureProbSolver(int failures_number, long ftime, int operating_hrs)
    {
        return;
    }

    static int binomial(uint8_t n, uint8_t k)
    {
        return factorial(n)/(factorial(k)*factorial(n-k));
    }

    static int factorial(int n)
    {
        return (n<1) ? 1 : n * factorial(n-1);
    }
};