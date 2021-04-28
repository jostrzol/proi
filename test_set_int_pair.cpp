#include <cassert>
#include <sstream>

#include "test_set_int_pair.h"

#define TEST_IN std::cout << "Running '" << __PRETTY_FUNCTION__ << "'... "
#define TEST_OUT std::cout << "PASS!\n"

void TestSetIntPair::TestConstructorDefault()
{
    TEST_IN;
    Set<IntPair> set;

    assert(set.Size() == 0);
    assert(set.Cap() == 1);
    TEST_OUT;
}

void TestSetIntPair::TestConstructorCopy()
{
    TEST_IN;
    Set<IntPair> set1{{1, 2}, {6, 6}, {-2, 4}, {3, -2}, {5, 0}};
    Set<IntPair> set2(set1);

    assert(set1 == set2);

    set2.Add({2, 6});
    assert(!set1.Contains({2, 6}));
    assert(set2.Contains({2, 6}));
    TEST_OUT;
}

void TestSetIntPair::TestConstructorMove()
{
    TEST_IN;
    Set<IntPair> set1{{1, 2}, {6, 6}, {-2, 4}, {3, -2}, {5, 0}};
    Set<IntPair> set2(std::move(set1));

    assert(set2.Size() == 5);
    assert(set2.Contains({1, 2}));
    assert(set2.Contains({6, 6}));
    assert(set2.Contains({-2, 4}));
    assert(set2.Contains({3, -2}));
    assert(set2.Contains({5, 0}));

    assert(set1.Size() == 0);
    TEST_OUT;
}

void TestSetIntPair::TestConstructorCap()
{
    TEST_IN;
    Set<IntPair> set(5);

    assert(set.Size() == 0);
    assert(set.Cap() == 8);
    TEST_OUT;
}

void TestSetIntPair::TestConstructorList()
{
    TEST_IN;
    Set<IntPair> set{{5, 4}, {6, 1}, {2, 6}};

    assert(set.Contains({5, 4}));
    assert(set.Contains({6, 1}));
    assert(set.Contains({2, 6}));

    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    TEST_OUT;
}

void TestSetIntPair::TestAssignmentCopy()
{
    TEST_IN;
    Set<IntPair> set1{{1, 2}, {6, 6}, {-2, 4}, {3, -2}, {5, 0}};
    Set<IntPair> set2{{4, 4}};
    set2 = set1;

    assert(set1 == set2);

    set2.Add({2, 6});
    assert(!set1.Contains({2, 6}));
    assert(set2.Contains({2, 6}));
    TEST_OUT;
}

void TestSetIntPair::TestAssignmentMove()
{
    TEST_IN;
    Set<IntPair> set1{{1, 2}, {6, 6}, {-2, 4}, {3, -2}, {5, 0}};
    Set<IntPair> set2{{4, 4}};
    set2 = std::move(set1);

    assert(set2.Size() == 5);
    assert(set2.Contains({1, 2}));
    assert(set2.Contains({6, 6}));
    assert(set2.Contains({-2, 4}));
    assert(set2.Contains({3, -2}));
    assert(set2.Contains({5, 0}));
    assert(!set2.Contains({4, 4}));

    assert(set1.Size() == 0);
    TEST_OUT;
}

void TestSetIntPair::TestAdd()
{
    TEST_IN;
    Set<IntPair> set{{4, 3}};
    assert(set.Size() == 1);
    assert(set.Cap() == 1);
    assert(set.Contains({4, 3}));

    set.Add({6, -1});
    assert(set.Size() == 2);
    assert(set.Cap() == 2);
    assert(set.Contains({4, 3}));
    assert(set.Contains({6, -1}));

    set.Add({-2, 2});
    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    assert(set.Contains({4, 3}));
    assert(set.Contains({6, -1}));
    assert(set.Contains({-2, 2}));

    set.Add({-2, 2});
    assert(set.Size() == 3);
    assert(set.Cap() == 4);
    assert(set.Contains({4, 3}));
    assert(set.Contains({6, -1}));
    assert(set.Contains({-2, 2}));
    TEST_OUT;
}

void TestSetIntPair::TestRemove()
{
    TEST_IN;
    Set<IntPair> set{{4, 2}, {7, 1}};
    set.Remove({4, 2});

    assert(set.Size() == 1);
    assert(set.Cap() == 2);

    assert(!set.Contains({4, 2}));
    assert(set.Contains({7, 1}));

    set.Remove({4, 2});

    assert(set.Size() == 1);
    assert(set.Cap() == 2);

    assert(!set.Contains({4, 2}));
    assert(set.Contains({7, 1}));
    TEST_OUT;
}

void TestSetIntPair::TestContains()
{
    TEST_IN;
    Set<IntPair> set{{4, 2}, {7, 1}};

    assert(set.Contains({4, 2}));
    assert(set.Contains({7, 1}));
    assert(!set.Contains({0, 2}));
    assert(!set.Contains({4, 1}));
    TEST_OUT;
}

void TestSetIntPair::TestSize()
{
    TEST_IN;
    Set<IntPair> set;

    std::size_t expected = 0;
    for (int i = -50; i < 50; i++)
    {
        set.Add({i, 5});
        expected++;
        assert(set.Size() == expected);
    }
    TEST_OUT;
}

void TestSetIntPair::TestCap()
{
    TEST_IN;
    Set<IntPair> set;

    std::size_t expected = 1;
    for (int i = -50; i < 50; i++)
    {
        set.Add({i, 5});
        assert(set.Cap() == expected);
        if (set.Size() == set.Cap())
        {
            expected *= 2;
        }
    }
    TEST_OUT;
}

void TestSetIntPair::TestUnion()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    Set<IntPair> set = set1.Union(set2);

    assert(set.Size() == 7);
    assert(set.Cap() == 16);

    assert(set.Contains({5, 4}));
    assert(set.Contains({7, 2}));
    assert(set.Contains({4, 1}));
    assert(set.Contains({2, 2}));
    assert(set.Contains({14, 3}));
    assert(set.Contains({-1, 2}));
    assert(set.Contains({66, 233}));
    TEST_OUT;
}

void TestSetIntPair::TestDiffirence()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    Set<IntPair> set = set1.Difference(set2);

    assert(set.Size() == 3);
    assert(set.Cap() == 8);

    assert(set.Contains({7, 2}));
    assert(set.Contains({4, 1}));
    assert(set.Contains({14, 3}));
    assert(!set.Contains({5, 4}));
    assert(!set.Contains({2, 2}));
    TEST_OUT;
}

void TestSetIntPair::TestIntersection()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    Set<IntPair> set = set1.Intersection(set2);

    assert(set.Size() == 2);
    assert(set.Cap() == 4);

    assert(set.Contains({5, 4}));
    assert(set.Contains({2, 2}));
    TEST_OUT;
}

void TestSetIntPair::TestLT()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    assert(set2 < set1);
    assert(!(set1 < set2));
    TEST_OUT;
}

void TestSetIntPair::TestLE()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};
    Set<IntPair> set3{{5, 4}, {6, 2}, {8, 7}, {66, 2}};

    assert(set2 <= set1);
    assert(!(set1 <= set2));
    assert(set2 <= set3);
    TEST_OUT;
}

void TestSetIntPair::TestGT()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    assert(set1 > set2);
    assert(!(set2 > set1));
    TEST_OUT;
}

void TestSetIntPair::TestGE()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};
    Set<IntPair> set3{{5, 4}, {6, 2}, {8, 7}, {66, 2}};

    assert(set1 >= set2);
    assert(!(set2 >= set1));
    assert(set2 >= set3);
    TEST_OUT;
}

void TestSetIntPair::TestEQ()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};
    Set<IntPair> set3{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    assert(set2 == set3);
    assert(!(set1 == set2));
    TEST_OUT;
}

void TestSetIntPair::TestNE()
{
    TEST_IN;
    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};
    Set<IntPair> set2{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};
    Set<IntPair> set3{{5, 4}, {-1, 2}, {2, 2}, {66, 233}};

    assert(set1 != set2);
    assert(!(set2 != set3));
    TEST_OUT;
}

void TestSetIntPair::TestOStream()
{
    TEST_IN;
    std::stringstream ss;

    Set<IntPair> set1{{5, 4}, {7, 2}, {4, 1}, {2, 2}, {14, 3}};

    ss << set1;
    assert(ss.str() == "{(5, 4), (7, 2), (4, 1), (2, 2), (14, 3)}");
    TEST_OUT;
}

void TestSetIntPair::RunAll()
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

IntPair::IntPair(int number1, int number2) : number1(number1), number2(number2) {}

bool IntPair::operator==(const IntPair &other) { return number1 == other.number1 && number2 == other.number2; }

bool IntPair::operator!=(const IntPair &other) { return !operator==(other); }

std::ostream &operator<<(std::ostream &os, const IntPair &intPair)
{
    os << "(" << intPair.number1 << ", " << intPair.number2 << ")";
    return os;
}
