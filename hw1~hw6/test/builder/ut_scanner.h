#include "../../src/builder/scanner.h"

TEST(ScannerTest, ScanCircleShouldBeCorrect)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanTriangleShouldBeCorrect)
{
    std::string input = "Triangle (Vector ((5.00, 8.00), (8.00, 11.00)), Vector ((5.00, 8.00), (10.00, 8.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Triangle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(5.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(11.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(5.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(10.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(8.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanRectangleShouldBeCorrect)
{
    std::string input = "Rectangle (Vector ((20.00, 13.00), (16.00, 14.00)), Vector ((16.00, 14.00), (15.00, 10.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Rectangle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(20.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(13.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(16.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(16.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(15.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(10.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanCompoundShapeShouldBeCorrect)
{
    std::string input = "CompoundShape ()";
    Scanner scanner(input);
    ASSERT_EQ("CompoundShape", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanSimpleCompoundShapeShouldBeCorrect)
{
    std::vector<std::string> expectedToken = {"CompoundShape", "(", "Circle", "(" , "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                                   "(", "double", ",", "double", ")", ")", ")", ",",
                                                                    "Rectangle", "(" , "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                                      "(", "double", ",", "double", ")", ")", ",",
                                                                                       "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                                       "(", "double", ",", "double", ")", ")",")", ")"};
    std::vector<double> expectedDouble = {0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 5.0, 0.0};

    std::string input = "CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00))))";
    Scanner scanner(input);

    int pos = 0;
    for(auto token : expectedToken)
    {
        if(token == "double")
        {
            ASSERT_EQ(expectedDouble.at(pos), scanner.nextDouble());
            pos++;
        }
        else
        {
            ASSERT_EQ(token, scanner.next());
        }
    }
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, ScanComplexCompoundShapeShouldBeCorrect)
{
    std::vector<std::string> expectedToken = {"CompoundShape", "(", "CompoundShape", "(",
                                              "Circle", "(" , "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                             "(", "double", ",", "double", ")", ")", ")", ",",
                                              "Rectangle", "(" , "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                "(", "double", ",", "double", ")", ")", ",",
                                                                 "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                "(", "double", ",", "double", ")", ")",")", ")", ",",
                                              "CompoundShape", "(", "Circle", "(" , "Vector", "(", "(", "double", ",", "double", ")", ",",
                                                                                                   "(", "double", ",", "double", ")", ")", ")", ")", ")"};
    std::vector<double> expectedDouble = {0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 0.0, 5.0,
                                          0.0, 0.0, 5.0, 0.0,
                                          0.0, 0.0, 0.0, 3.0};

    std::string input = "CompoundShape (CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 5.00))), Rectangle (Vector ((0.00, 0.00), (0.00, 5.00)), Vector ((0.00, 0.00), (5.00, 0.00)))), CompoundShape (Circle (Vector ((0.00, 0.00), (0.00, 3.00)))))";
    Scanner scanner(input);

    int pos = 0;
    for(auto token : expectedToken)
    {
        if(token == "double")
        {
            ASSERT_EQ(expectedDouble.at(pos), scanner.nextDouble());
            pos++;
        }
        else
        {
            ASSERT_EQ(token, scanner.next());
        }
    }
    ASSERT_TRUE(scanner.isDone());
}

TEST(ScannerTest, NextShouldThrowExceptionWhenIsDone)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(")", scanner.next());

    ASSERT_ANY_THROW(scanner.next());
}

TEST(ScannerTest, NextDoubleShouldThrowExceptionWhenIsDone)
{
    std::string input = "Circle (Vector ((14.00, 2.00), (18.00, -4.00)))";
    Scanner scanner(input);
    ASSERT_EQ("Circle", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("Vector", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(14.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(2.0, scanner.nextDouble());
    ASSERT_EQ(")", scanner.next());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ("(", scanner.next());
    ASSERT_EQ(18.0, scanner.nextDouble());
    ASSERT_EQ(",", scanner.next());
    ASSERT_EQ(-4.0, scanner.nextDouble());

    ASSERT_ANY_THROW(scanner.nextDouble());
}