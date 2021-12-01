#include <iostream>
#include "../helper.hpp"
#include "gtest/gtest.h"

TEST(ProportionalTest, givenProperArgumentListResultIsProperlyEvaluated){
    testing::internal::CaptureStdout();

    std::vector<float> prod_p{0.67,0.19,0.14};
    std::vector<float> nondef_p{0.03,0.41,0.16};
    Solver::proportionalSolve(prod_p, nondef_p);

    std::string predictedOutput = "The proportions of production of 3 plants: 0.67 0.19 0.14 \n"
        "The probabilities of non-defective product coming from 3 plants: 0.03 0.41 0.16 \n"
        "The probability that the fault part comes from plant 1 equals: 73.8858%\n"
        "The probability that the fault part comes from plant 2 equals: 12.7444%\n"
        "The probability that the fault part comes from plant 3 equals: 13.3697%\n";
        std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(predictedOutput,output);
}

TEST(ProportionalTest, givenAnotherProperArgumentListResultIsProperlyEvaluated){
    testing::internal::CaptureStdout();

    std::vector<float> prod_p{0.35,0.15,0.5};
    std::vector<float> nondef_p{0.75,0.95,0.85};
    Solver::proportionalSolve(prod_p, nondef_p);

    std::string predictedOutput = "The proportions of production of 3 plants: 0.35 0.15 0.5 \n"
        "The probabilities of non-defective product coming from 3 plants: 0.75 0.95 0.85 \n"
        "The probability that the fault part comes from plant 1 equals: 51.4706%\n"
        "The probability that the fault part comes from plant 2 equals: 4.41177%\n"
        "The probability that the fault part comes from plant 3 equals: 44.1176%\n";
        std::string output = testing::internal::GetCapturedStdout();
    EXPECT_EQ(predictedOutput,output);
}

TEST(ProportionalTestException, givenBothOfArgumentVectorsEmptyCorrectExceptionIsThrown)
{
    std::vector<float> prod_p{};
    std::vector<float> nondef_p{};
    EXPECT_THROW({
        try
        {
            Solver::proportionalSolve(prod_p, nondef_p);
        }
        catch(const std::string& exceptionString)
        {
            EXPECT_EQ("Both vectors must contain at least 1 element.\n", exceptionString);
            throw;
        }
    }, std::string);
}

TEST(ProportionalTestException, givenArgumentVectorsOfNonEqualSizedCorrectExceptionIsThrown)
{
    std::vector<float> prod_p{0.35,0.15,0.5};
    std::vector<float> nondef_p{0.95,0.85};
    EXPECT_THROW({
        try
        {
            Solver::proportionalSolve(prod_p, nondef_p);
        }
        catch(const std::string& exceptionString)
        {
            EXPECT_EQ("Both vectors must be the same size.\n", exceptionString);
            throw;
        }
    }, std::string);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}