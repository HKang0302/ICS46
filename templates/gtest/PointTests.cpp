// PointTest.cpp
//
// ICS 46 Spring 2018
// Code Example
//
// This source file contains unit tests for our Point<CoordinateType>
// template class.

#include <gtest/gtest.h>
#include <cmath>
#include <string>
#include "Point.hpp"



TEST(PointTest, pointsWithIntCoordinatesHaveTheirGivenCoordinates)
{
    Point<int> p{3, -2, 5};
    EXPECT_EQ(3, p.x());
    EXPECT_EQ(-2, p.y());
    EXPECT_EQ(5, p.z());
}


TEST(PointTest, pointsWithDoubleCoordinatesHaveTheirGivenCoordinates)
{
    Point<double> p{3.5, 6.75, -2.125};
    EXPECT_EQ(3.5, p.x());
    EXPECT_EQ(6.75, p.y());
    EXPECT_EQ(-2.125, p.z());
}


TEST(PointTest, pointsWithStringCoordinatesAreStrangelyLegal)
{
    // It's legal to instantiate Point objects with string coordinates,
    // though you won't be able to do certain things to them -- in
    // particular, you won't be able to calculate a distance between
    // them.

    Point<std::string> p{"Boo", "is", "perfect"};
    EXPECT_EQ(std::string{"Boo"}, p.x());
    EXPECT_EQ(std::string{"is"}, p.y());
    EXPECT_EQ(std::string{"perfect"}, p.z());
}


TEST(PointTest, coordinatesCanBeUpdated)
{
    Point<int> p{1, 2, 3};

    p.x() = -4;
    p.y() = 9;
    p.z() = -5;

    EXPECT_EQ(p.x(), -4);
    EXPECT_EQ(p.y(), 9);
    EXPECT_EQ(p.z(), -5);
}


TEST(PointTest, distancesAreCalculatedCorrectly)
{
    // (2, 3, 6, 7) is a Pythagorean quadruple

    Point<double> p1{10, -6, 1};
    Point<double> p2{12, -9, 7};

    EXPECT_NEAR(7.0, p1.distanceFrom(p2), 0.0001);
}


TEST(PointTests, pointsOfTheSameTypeCanBeCopied)
{
    Point<double> p1{4, 5, 6};
    Point<double> p2{p1};

    EXPECT_EQ(p2.x(), 4);
    EXPECT_EQ(p2.y(), 5);
    EXPECT_EQ(p2.z(), 6);
}


TEST(PointTests, pointsOfCompatibleTypesCanBeCopied)
{
    Point<float> p1{-1, 2, -3};
    Point<double> p2{p1};

    EXPECT_EQ(p2.x(), -1);
    EXPECT_EQ(p2.y(), 2);
    EXPECT_EQ(p2.z(), -3);
}


TEST(PointTests, pointsOfTheSameTypeCanBeAssigned)
{
    Point<double> p1{4, 5, 6};
    Point<double> p2{6, 7, 8};
    p1 = p2;

    EXPECT_EQ(p1.x(), 6);
    EXPECT_EQ(p1.y(), 7);
    EXPECT_EQ(p1.z(), 8);
}


TEST(PointTests, pointsOfCompatibleTypesCanBeAssigned)
{
    Point<float> p1{-1, 2, -3};
    Point<double> p2{4, -5, 6};
    p2 = p1;

    EXPECT_EQ(p2.x(), -1);
    EXPECT_EQ(p2.y(), 2);
    EXPECT_EQ(p2.z(), -3);
}


// You might be wondering why there are no unit tests in cases where the
// types are incompatible.  The reason is simple: In a statically-typed
// language like C++, in which programs won't compile with type errors
// in them, you can't write and then run unit tests that won't compile.
// One of the benefits of a static type system is that there's no need
// to worry about testing these kinds of cases; the tradeoff is that
// the type system has more syntactic and semantic territory to understand.

