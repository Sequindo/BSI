#include <iostream>

class Solver {

public:

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

    static int binomial(uint8_t n, uint8_t k)
    {
        return factorial(n)/(factorial(k)*factorial(n-k));
    }

    static int factorial(int n)
    {
        return (n<1) ? 1 : n * factorial(n-1);
    }
};