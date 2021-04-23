#pragma once

#include <iostream>

#include "set.h"

class IntPair
{
public:
    IntPair(int number1 = 0, int number2 = 0);

    bool operator==(const IntPair &other);
    bool operator!=(const IntPair &other);

    friend std::ostream &operator<<(std::ostream &os, const IntPair &intPair);

private:
    int number1;
    int number2;
};

class TestSetIntPair
{
public:
    static void RunAll();

    static void TestConstructorDefault();
    static void TestConstructorCopy();
    static void TestConstructorMove();
    static void TestConstructorCap();
    static void TestConstructorList();

    static void TestAssignmentCopy();
    static void TestAssignmentMove();

    static void TestAdd();
    static void TestRemove();
    static void TestContains();

    static void TestSize();
    static void TestCap();

    static void TestUnion();
    static void TestDiffirence();
    static void TestIntersection();

    static void TestLT();
    static void TestLE();
    static void TestGT();
    static void TestGE();
    static void TestEQ();
    static void TestNE();

    static void TestOStream();
};