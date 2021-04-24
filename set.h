#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>
#include <initializer_list>

template <class T>
class Set
{
public:
    Set();
    Set(std::initializer_list<T> elements);
    Set(std::size_t size_);
    Set(const Set<T> &other);
    Set(Set<T> &&other);
    ~Set();

    Set<T> &operator=(const Set<T> &other);
    Set<T> &operator=(Set<T> &&other);

    void Add(const T &element);
    void Remove(const T &element);
    bool Contains(const T &element) const;

    std::size_t Size();
    std::size_t Cap();

    Set<T> Union(const Set<T> &other);
    Set<T> Difference(const Set<T> &other);
    Set<T> Intersection(const Set<T> &other);

    bool operator<(const Set<T> &other);
    bool operator<=(const Set<T> &other);
    bool operator>(const Set<T> &other);
    bool operator>=(const Set<T> &other);
    bool operator==(const Set<T> &other);
    bool operator!=(const Set<T> &other);

    template <class U>
    friend std::ostream &operator<<(std::ostream &os, const Set<U> &set);

private:
    std::size_t index(const T &element) const;
    void allocate(std::size_t size);

    std::size_t size;
    std::size_t cap;
    T *arr;
};

#pragma region constructors

template <class T>
Set<T>::Set() : size(0), cap(1), arr(new T[cap])
{
}

template <class T>
Set<T>::Set(std::initializer_list<T> elements)
    : Set(elements.size())
{
    size = elements.size();
    std::copy(elements.begin(), elements.end(), arr);
}

template <class T>
Set<T>::Set(std::size_t size_)
    : size(0)
{
    allocate(size_);
}

template <class T>
Set<T>::Set(const Set<T> &other)
    : Set(other.size)
{
    size = other.size;
    std::copy(other.arr, other.arr + size, arr);
}

template <class T>
Set<T>::Set(Set<T> &&other)
    : size(other.size), cap(other.cap), arr(other.arr)
{
    other.arr = NULL;
    other.size = 0;
}

template <class T>
Set<T>::~Set() { delete[] arr; }

#pragma endregion constructors

template <class T>
Set<T> &Set<T>::operator=(const Set<T> &other)
{
    if (&other == this)
        return other;

    allocate(other.size);
    size = other.size;
    std::copy(other.arr, other.arr + other.size, arr);

    return *this;
}

template <class T>
Set<T> &Set<T>::operator=(Set<T> &&other)
{
    size = other.size;
    cap = other.cap;
    arr = other.arr;

    other.arr = NULL;
    other.cap = 0;
    other.size = 0;

    return *this;
}

template <class T>
void Set<T>::Add(const T &element)
{
    if (Contains(element))
        return;

    if (size == cap)
    {
        if (cap != 0)
        {
            T *newArr = new T[2 * cap];
            std::move(arr, arr + cap, newArr);
            delete[] arr;
            arr = newArr;
            cap = 2 * cap;
        }
        else
        {
            allocate(1);
        }
    }
    arr[size++] = element;
}

template <class T>
void Set<T>::Remove(const T &element)
{
    std::size_t i = index(element);
    if (i == cap)
        return;

    arr[i] = arr[size-- - 1];
}

template <class T>
bool Set<T>::Contains(const T &element) const
{
    return index(element) != cap;
}

template <class T>
std::size_t Set<T>::Size()
{
    return size;
}

template <class T>
std::size_t Set<T>::Cap()
{
    return cap;
}

template <class T>
Set<T> Set<T>::Union(const Set<T> &other)
{
    const Set<T> &smaller = size < other.size ? *this : other;
    const Set<T> &bigger = &smaller == this ? other : *this;

    Set<T> newSet(2 * bigger.size);
    newSet.size = bigger.size;
    std::copy(bigger.arr, bigger.arr + bigger.size, newSet.arr);

    for (std::size_t i = 0; i < smaller.size; i++)
    {
        newSet.Add(smaller.arr[i]);
    }

    return newSet;
}

template <class T>
Set<T> Set<T>::Difference(const Set<T> &other)
{
    Set<T> newSet(size);
    for (std::size_t i = 0; i < size; i++)
    {
        if (!other.Contains(arr[i]))
            newSet.Add(arr[i]);
    }
    return newSet;
}

template <class T>
Set<T> Set<T>::Intersection(const Set<T> &other)
{
    const Set<T> &smaller = size < other.size ? *this : other;
    const Set<T> &bigger = &smaller == this ? other : *this;

    Set<T> newSet(smaller.size);
    for (std::size_t i = 0; i < smaller.size; i++)
    {
        if (bigger.Contains(smaller.arr[i]))
            newSet.Add(smaller.arr[i]);
    }
    return newSet;
}

#pragma region comparison

template <class T>
bool Set<T>::operator<(const Set<T> &other)
{
    return size < other.size;
}

template <class T>
bool Set<T>::operator<=(const Set<T> &other)
{
    return size <= other.size;
}

template <class T>
bool Set<T>::operator>(const Set<T> &other)
{
    return size > other.size;
}

template <class T>
bool Set<T>::operator>=(const Set<T> &other)
{
    return size >= other.size;
}

template <class T>
bool Set<T>::operator==(const Set<T> &other)
{
    if (size != other.size)
        return false;

    for (std::size_t i = 0; i < size; i++)
    {
        if (!other.Contains(arr[i]))
            return false;
    }
    return true;
}

template <class T>
bool Set<T>::operator!=(const Set<T> &other)
{
    return !(*this == other);
}

#pragma endregion comparison

template <class T>
std::size_t Set<T>::index(const T &element) const
{
    for (std::size_t i = 0; i < size; i++)
    {
        if (arr[i] == element)
            return i;
    }
    return cap;
}

template <class T>
void Set<T>::allocate(std::size_t size_)
{
    cap = 1;
    size = 0;
    while (cap < size_)
        cap *= 2;
    arr = new T[cap];
}

template <class U>
std::ostream &operator<<(std::ostream &os, const Set<U> &set)
{
    os << "{";
    for (std::size_t i = 0; i < set.size; i++)
    {
        os << set.arr[i];
        if (i < set.size - 1)
        {
            os << ", ";
        }
    }
    os << "}";
    return os;
}