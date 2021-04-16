#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>

template <class T>
class Set
{
public:
    Set();
    Set(std::size_t size_);
    ~Set();

    void Add(const T &element);
    void Remove(const T &element);
    bool Contains(const T &element);

    std::size_t Size();

    Set<T> Union(const Set<T> &other);
    Set<T> Diffirence(const Set<T> &other);
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
    std::size_t index(const T &element);

    std::size_t size;
    std::size_t cap;
    T *arr;
};

template <class T>
Set<T>::Set() : size(0), cap(1), arr(new T[cap]) {}

template <class T>
Set<T>::Set(std::size_t size_) : size(0), cap(1)
{
    while (cap < size_)
        cap << 1;
    arr = new T[cap];
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
bool Set<T>::Contains(const T &element)
{
    return index(element) != cap;
}

template <class T>
std::size_t Set<T>::Size()
{
    return size;
}

template <class T>
Set<T> Set<T>::Union(const Set<T> &other)
{
    std::size_t newSize = size > other.size ? size : other.size;
    Set<T> newSet(newSize);
    std::copy(arr, arr + size, newSet.arr);
    std::copy(arr + size, arr + size + newSet.size, newSet.arr + newSet.size);
    return newSet;
}

template <class T>
Set<T> Set<T>::Diffirence(const Set<T> &other)
{
    Set<T> newSet(cap);
    std::copy(arr, arr + size, newSet.arr);
    for (std::size_t i = 0; i < other.size; i++)
        newSet.Remove(other.arr[i]);
    return newSet;
}

template <class T>
Set<T> Set<T>::Intersection(const Set<T> &other)
{
    Set<T> &smaller = size < other.size ? *this : other;
    Set<T> &bigger = &smaller == this ? other : *this;

    Set<T> newSet(smaller.cap);
    for (std::size_t i = 0; i < smaller.size; i++)
    {
        if (other.Contains(smaller.arr[i]))
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
std::size_t Set<T>::index(const T &element)
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
        os << set.arr[i] << ", ";
    }
    os << "}";
    return os;
}