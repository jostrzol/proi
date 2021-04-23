#pragma once

#include "set.h"

class TestSetInt
{
public:
    static void RunAll();

    static void TestConstructorDefault();
    static void TestConstructorCopy();
    static void TestConstructorCap();
    static void TestConstructorList();

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