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

TEST(ParallelReliabilityTest, givenProperArgumentsThenCalculateProbabilityOfRemainingOperativeForEachCombination)
{
    int devices_num = 4;
    float rel_factor = 0.9; //data from exercise 37
    testing::internal::CaptureStdout();

    Solver::parallelSolve(devices_num, rel_factor);
    std::string output = testing::internal::GetCapturedStdout();
    std::string predictedOutput = "Common reliability rate is 0.9. Therefore common failure rate is 0.1.\n"
        "Probability that 0 out of 4 units will remain operative: 0.0001\n"
        "Probability that 1 out of 4 units will remain operative: 0.0036\n"
        "Probability that 2 out of 4 units will remain operative: 0.0486\n"
        "Probability that 3 out of 4 units will remain operative: 0.2916\n"
        "Probability that 4 out of 4 units will remain operative: 0.6561\n";
    EXPECT_EQ(predictedOutput, output);
}

TEST(BinomialTest, givenProperArgumentsThenBinomialIsProperlyCalculated)
{
    EXPECT_EQ(10, Solver::binomial(5,3));
    EXPECT_EQ(220, Solver::binomial(12,3));
    EXPECT_EQ(455, Solver::binomial(15,3));
    EXPECT_EQ(1140, Solver::binomial(20,3));
}

TEST(FactorialTest, givenProperArgumentThenFactorialIsProperlyCalculated)
{
    std::vector<int> input = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    std::vector<int> output = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};
    for(int i=0;i<input.size();i++)
    {
        EXPECT_EQ(output.at(i), Solver::factorial(input.at(i)));
    }
}

TEST(CardDeckTest, given1AsArgumentProperlyCalculateChancesOfDiamondsOnDeckTop)
{
    testing::internal::CaptureStdout();
    std::string test_input = "1\n";
    std::stringstream fake_input(test_input);

    Solver::cardDeckSolver(fake_input);
    std::string output = testing::internal::GetCapturedStdout();
    std::string predictedOutput = "Insert which card do you want to check: \n"
        "1 - diamond, 2 - black, 3 - nine\n"
        "Probability that a card chosen by you is on the top of the deck equals: 25 %\n";
    EXPECT_EQ(output, predictedOutput);
}

TEST(CardDeckTest, given1AsArgumentProperlyCalculateChancesOfBlacksOnDeckTop)
{
    testing::internal::CaptureStdout();
    std::string test_input = "2\n";
    std::stringstream fake_input(test_input);

    Solver::cardDeckSolver(fake_input);
    std::string output = testing::internal::GetCapturedStdout();
    std::string predictedOutput = "Insert which card do you want to check: \n"
        "1 - diamond, 2 - black, 3 - nine\n"
        "Probability that a card chosen by you is on the top of the deck equals: 50 %\n";
    EXPECT_EQ(output, predictedOutput);
}

TEST(CardDeckTest, given1AsArgumentProperlyCalculateChancesOfNinesOnDeckTop)
{
    testing::internal::CaptureStdout();
    std::string test_input = "3\n";
    std::stringstream fake_input(test_input);

    Solver::cardDeckSolver(fake_input);
    std::string output = testing::internal::GetCapturedStdout();
    std::string predictedOutput = "Insert which card do you want to check: \n"
        "1 - diamond, 2 - black, 3 - nine\n"
        "Probability that a card chosen by you is on the top of the deck equals: 7.69231 %\n";
    EXPECT_EQ(output, predictedOutput);
}


int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}