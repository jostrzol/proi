#include <cassert>
#include <sstream>

#include "test_set_int.h"

void TestSetInt::TestConstructorDefault()
{
    Set<int> set;

    assert(set.Size() == 0);
    assert(set.Cap() == 1);
}

void TestSetInt::TestConstructorCopy()
{
    Set<int> set1{1, 6, -2, 3, 5};
    Set<int> set2(set1);

    assert(set1 == set2);
    assert(set1.Cap() == set2.Cap());
}

void TestSetInt::TestConstructorCap()
{
    Set<int> set(5);

    assert(set.Size() == 0);
    assert(set.Cap() == 8);
}

void TestSetInt::TestConstructorList()
{
    Set<int> set{5, 6, 2};

    assert(set.Contains(5));
    assert(set.Contains(6));
    assert(set.Contains(2));

    assert(set.Size() == 3);
    assert(set.Cap() == 4);
}

void TestSetInt::TestAdd()
{
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
}

void TestSetInt::TestRemove()
{
    Set<int> set{4, 7};
    set.Remove(4);

    assert(set.Size() == 1);
    assert(set.Cap() == 2);

    assert(!set.Contains(4));
    assert(set.Contains(7));
}

void TestSetInt::TestContains()
{
    Set<int> set{4, 7};

    assert(set.Contains(4));
    assert(set.Contains(7));
    assert(!set.Contains(0));
    assert(!set.Contains(9));
}

void TestSetInt::TestSize()
{
    Set<int> set;

    std::size_t expected = 0;
    for (int i = -50; i < 50; i++)
    {
        set.Add(i);
        expected++;
        assert(set.Size() == expected);
    }
}

void TestSetInt::TestCap()
{
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
}

void TestSetInt::TestUnion()
{
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
}

void TestSetInt::TestDiffirence()
{
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
}

void TestSetInt::TestIntersection()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    Set<int> set = set1.Intersection(set2);

    assert(set.Size() == 2);
    assert(set.Cap() == 4);

    assert(set.Contains(5));
    assert(set.Contains(2));
}

void TestSetInt::TestLT()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    assert(set2 < set1);
    assert(!(set1 < set2));
}

void TestSetInt::TestLE()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, 6, 8, 66};

    assert(set2 <= set1);
    assert(!(set1 <= set2));
    assert(set2 <= set3);
}

void TestSetInt::TestGT()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};

    assert(set1 > set2);
    assert(!(set2 > set1));
}

void TestSetInt::TestGE()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, 6, 8, 66};

    assert(set1 >= set2);
    assert(!(set2 >= set1));
    assert(set2 >= set3);
}

void TestSetInt::TestEQ()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, -1, 2, 66};

    assert(set2 == set3);
    assert(!(set1 == set2));
}

void TestSetInt::TestNE()
{
    Set<int> set1{5, 7, 4, 2, 14};
    Set<int> set2{5, -1, 2, 66};
    Set<int> set3{5, -1, 2, 66};

    assert(set1 != set2);
    assert(!(set2 != set3));
}

void TestSetInt::TestOStream()
{
    std::stringstream ss;

    Set<int> set1{5, 7, 4, 2, 14};

    ss << set1;
    assert(ss.str() == "{5, 7, 4, 2, 14}");
}

void TestSetInt::RunAll()
{
    TestConstructorDefault();
    TestConstructorCopy();
    TestConstructorCap();
    TestConstructorList();

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
