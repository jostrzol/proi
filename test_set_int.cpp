#include <cassert>
#include <sstream>

#include "test_set_int.h"

#define TEST_IN std::cout << "Running '" << __PRETTY_FUNCTION__ << "'... "
#define TEST_OUT std::cout << "PASS!\n"

void TestSetInt::TestConstructorDefault()
{
    TEST_IN;
    Set<int> set;

    assert(set.Size() == 0);
    assert(set.Cap() == 1);
    TEST_OUT;
}

void TestSetInt::TestConstructorCopy()
{
    TEST_IN;
    Set<int> set1{1, 6, -2, 3, 5};
    Set<int> set2(set1);

    assert(set1 == set2);

    set2.Add(2);
    assert(!set1.Contains(2));
    assert(set2.Contains(2));
    TEST_OUT;
}

void TestSetInt::TestConstructorMove()
{
    TEST_IN;
    Set<int> set1{1, 6, -2, 3, 5};
    Set<int> set2(std::move(set1));

    assert(set2.Size() == 5);
    assert(set2.Contains(1));
    assert(set2.Contains(6));
    assert(set2.Contains(-2));
    assert(set2.Contains(3));
    assert(set2.Contains(5));

    assert(set1.Size() == 0);
    TEST_OUT;
}

void TestSetInt::TestConstructorCap()
{
    TEST_IN;
    Set<int> set(5);

    assert(set.Size() == 0);
    assert(set.Cap() == 8);
    TEST_OUT;
}

void TestSetInt::TestConstructorList()
{
    TEST_IN;
    Set<int> set{5, 6, 2};

    assert(set.Contains(5));
    assert(set.Contains(6));
    assert(set.Contains(2));

    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    TEST_OUT;
}

void TestSetInt::TestAssignmentCopy()
{
    TEST_IN;
    Set<int> set1{1, 6, -2, 3, 5};
    Set<int> set2{7};
    set2 = set1;

    assert(set1 == set2);

    set2.Add(2);
    assert(!set1.Contains(2));
    assert(set2.Contains(2));
    TEST_OUT;
}

void TestSetInt::TestAssignmentMove()
{
    TEST_IN;
    Set<int> set1{1, 6, -2, 3, 5};
    Set<int> set2{7};
    set2 = std::move(set1);

    assert(set2.Size() == 5);
    assert(set2.Contains(1));
    assert(set2.Contains(6));
    assert(set2.Contains(-2));
    assert(set2.Contains(3));
    assert(set2.Contains(5));
    assert(!set2.Contains(7));

    assert(set1.Size() == 0);
    TEST_OUT;
}

void TestSetInt::TestAdd()
{
    TEST_IN;
    Set<int> set{4};
    assert(set.Size() == 1);
    assert(set.Cap() == 1);
    assert(set.Contains(4));

    set.Add(6);
    assert(set.Size() == 2);
    assert(set.Cap() == 2);
    assert(set.Contains(4));
    assert(set.Contains(6));

    set.Add(-2);
    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    assert(set.Contains(4));
    assert(set.Contains(6));
    assert(set.Contains(-2));

    set.Add(-2);
    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    assert(set.Contains(4));
    assert(set.Contains(6));
    assert(set.Contains(-2));
    TEST_OUT;
}

void TestSetInt::TestRemove()
{
    TEST_IN;
    Set<int> set{4, 7};
    set.Remove(4);

    assert(set.Size() == 1);
    assert(set.Cap() == 2);

    assert(!set.Contains(4));
    assert(set.Contains(7));

    set.Remove(4);
    assert(set.Size() == 1);
    assert(set.Cap() == 2);

    assert(!set.Contains(4));
    assert(set.Contains(7));
    TEST_OUT;
}

void TestSetInt::TestContains()
{
    TEST_IN;
    Set<int> set{4, 7};

    assert(set.Contains(4));
    assert(set.Contains(7));
    assert(!set.Contains(0));
    assert(!set.Contains(9));
    TEST_OUT;
}

void TestSetInt::TestSize()
{
    TEST_IN;
    Set<int> set;

    std::size_t expected = 0;
    for (int i = -50; i < 50; i++)
    {
        set.Add(i);
        expected++;
        assert(set.Size() == expected);
    }
    TEST_OUT;
}

void TestSetInt::TestCap()
{
    TEST_IN;
    Set<int> set;

    std::size_t expected = 1;
    for (int i = -50; i < 50; i++)
    {
        set.Add(i);
        assert(set.Cap() == expected);
        if (set.Size() == set.Cap())
        {
            expected *= 2;
        }
    }
    TEST_OUT;
}

void TestSetInt::TestUnion()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    Set<int> set = set1.Union(set2);

    assert(set.Size() == 7);
    assert(set.Cap() == 16);

    assert(set.Contains(5));
    assert(set.Contains(7));
    assert(set.Contains(4));
    assert(set.Contains(2));
    assert(set.Contains(14));
    assert(set.Contains(-1));
    assert(set.Contains(66));
    TEST_OUT;
}

void TestSetInt::TestDiffirence()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    Set<int> set = set1.Difference(set2);

    assert(set.Size() == 3);
    assert(set.Cap() == 8);

    assert(set.Contains(7));
    assert(set.Contains(4));
    assert(set.Contains(14));
    assert(!set.Contains(5));
    assert(!set.Contains(2));
    TEST_OUT;
}

void TestSetInt::TestIntersection()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    Set<int> set = set1.Intersection(set2);

    assert(set.Size() == 2);
    assert(set.Cap() == 4);

    assert(set.Contains(5));
    assert(set.Contains(2));
    TEST_OUT;
}

void TestSetInt::TestLT()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    assert(set2 < set1);
    assert(!(set1 < set2));
    TEST_OUT;
}

void TestSetInt::TestLE()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, 6, 8, 66};

    assert(set2 <= set1);
    assert(!(set1 <= set2));
    assert(set2 <= set3);
    TEST_OUT;
}

void TestSetInt::TestGT()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    assert(set1 > set2);
    assert(!(set2 > set1));
    TEST_OUT;
}

void TestSetInt::TestGE()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, 6, 8, 66};

    assert(set1 >= set2);
    assert(!(set2 >= set1));
    assert(set2 >= set3);
    TEST_OUT;
}

void TestSetInt::TestEQ()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, -1, 2, 66};

    assert(set2 == set3);
    assert(!(set1 == set2));
    TEST_OUT;
}

void TestSetInt::TestNE()
{
    TEST_IN;
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, -1, 2, 66};

    assert(set1 != set2);
    assert(!(set2 != set3));
    TEST_OUT;
}

void TestSetInt::TestOStream()
{
    TEST_IN;
    std::stringstream ss;

    Set<int> set1{5, 7, 4, 2, 14};

    ss << set1;
    assert(ss.str() == "{5, 7, 4, 2, 14}");
    TEST_OUT;
}

void TestSetInt::RunAll()
{
    TestConstructorDefault();
    TestConstructorCopy();
    TestConstructorMove();
    TestConstructorCap();
    TestConstructorList();

    TestAssignmentCopy();
    TestAssignmentMove();

    TestAdd();
    TestRemove();
    TestContains();

    TestSize();
    TestCap();

    TestUnion();
    TestDiffirence();
    TestIntersection();

    TestLT();
    TestLE();
    TestGT();
    TestGE();
    TestEQ();
    TestNE();

    TestOStream();
}
