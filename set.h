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
    Set(std::size_t cap_);
    Set(const Set<T> &other);
    ~Set();

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

    std::size_t size;
    std::size_t cap;
    T *arr;
};

template <class T>
Set<T>::Set() : size(0), cap(1), arr(new T[cap]) {}

template <class T>
Set<T>::Set(std::initializer_list<T> elements)
    : Set(elements.size())
{
    size = elements.size();
    std::copy(elements.begin(), elements.end(), arr);
}

template <class T>
Set<T>::Set(std::size_t cap_) : size(0), cap(1)
{
    while (cap < cap_)
        cap *= 2;
    arr = new T[cap];
}

template <class T>
Set<T>::Set(const Set<T> &other)
    : size(other.size), cap(other.cap), arr(new T[size])
{
    std::copy(other.arr, other.arr + size, arr);
}

template <class T>
Set<T>::~Set() { delete[] arr; }

template <class T>
void Set<T>::Add(const T &element)
{
    if (Contains(element))
        return;

    if (size == cap)
    {
        T *newArr = new T[2 * cap];
        std::copy(arr, arr + cap, newArr);
        delete[] arr;
        arr = newArr;
        cap = 2 * cap;
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
    Set<T> newSet(*this);

    for (std::size_t i = 0; i < other.size; i++)
        newSet.Remove(other.arr[i]);
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