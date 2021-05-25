#pragma once

#include <string>
#include <chrono>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <memory>

// Returns the given duration in <Hours>:<Minutes> format
std::string MinutesToDaytime(std::chrono::minutes minutes);

template <class K, class V>
class UnorderedMapSortedIterator
{
public:
    using iterator = UnorderedMapSortedIterator<K, V>;
    using iterator_category = std::forward_iterator_tag;
    using difference_type = long long int;
    using value_type = typename std::unordered_map<K, V>::iterator::value_type;
    using pointer = typename std::unordered_map<K, V>::iterator::pointer;
    using reference = typename std::unordered_map<K, V>::iterator::reference;

    UnorderedMapSortedIterator(std::unordered_map<K, V> &map);
    UnorderedMapSortedIterator(const iterator &other);

    iterator begin();
    iterator end();

    pointer operator->();
    reference operator*();

    // Prefix increment
    iterator &operator++();

    // Postfix increment
    iterator operator++(int);

    bool operator==(const iterator &other);
    bool operator!=(const iterator &other);

private:
    std::unordered_map<K, V> &map;
    std::shared_ptr<std::vector<K>> keysSorted;
    std::size_t i = 0;
};

template <class K, class V>
UnorderedMapSortedIterator<K, V>::UnorderedMapSortedIterator(std::unordered_map<K, V> &map)
    : map(map), keysSorted(std::make_shared<std::vector<K>>())
{
    keysSorted->reserve(map.size());

    std::for_each(map.begin(), map.end(), [&](const std::pair<K, V> &p)
                  { keysSorted->push_back(p.first); });

    std::sort(keysSorted->begin(), keysSorted->end());
}

template <class K, class V>
UnorderedMapSortedIterator<K, V>::UnorderedMapSortedIterator(const UnorderedMapSortedIterator<K, V> &other)
    : map(other.map), keysSorted(other.keysSorted), i(other.i) {}

template <class K, class V>
UnorderedMapSortedIterator<K, V> UnorderedMapSortedIterator<K, V>::begin()
{
    iterator result(*this);
    result.i = 0;
    return result;
}

template <class K, class V>
UnorderedMapSortedIterator<K, V> UnorderedMapSortedIterator<K, V>::end()
{
    iterator result(*this);
    result.i = keysSorted->size() - 1;
    return result;
}
template <class K, class V>
bool UnorderedMapSortedIterator<K, V>::operator==(const UnorderedMapSortedIterator<K, V> &other)
{
    return &map == &other.map && i == other.i;
}

template <class K, class V>
bool UnorderedMapSortedIterator<K, V>::operator!=(const UnorderedMapSortedIterator<K, V> &other)
{
    return &map != &other.map || i != other.i;
}

template <class K, class V>
UnorderedMapSortedIterator<K, V> UnorderedMapSortedIterator<K, V>::operator++(int)
{
    i++;
    return *this;
}

template <class K, class V>
UnorderedMapSortedIterator<K, V> &UnorderedMapSortedIterator<K, V>::operator++()
{
    auto tmp = *this;
    ++(*this);
    return tmp;
}

template <class K, class V>
typename UnorderedMapSortedIterator<K, V>::pointer UnorderedMapSortedIterator<K, V>::operator->()
{
    const auto &key = (*keysSorted)[i];
    return map.find(key).operator->();
}

template <class K, class V>
typename UnorderedMapSortedIterator<K, V>::reference UnorderedMapSortedIterator<K, V>::operator*()
{
    const auto &key = (*keysSorted)[i];
    return map.find(key).operator*();
}