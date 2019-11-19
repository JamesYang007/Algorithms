#pragma once

// Header file containing generic sorting algorithm
//
#include <type_traits>
#include <utility>
#include <iostream>
#include <vector>
#include <unordered_map>
#include <array>

namespace algos {

////////////////////////////////////////////////////////////////
// Quicksort Implementation
////////////////////////////////////////////////////////////////
namespace details {

struct AscendingComp 
{
    template <class T>
    int operator()(const T& x, const T& y)
    {
        if (x < y) {
            return -1;
        }
        else if (x == y) {
            return 0;
        }
        else {
            return 1;
        }
    }
};

// Assumes that beg != end (there is at least one element to sort)
// Only qsort will call this function
template <class Container, class Comp>
std::pair<int, int>
inline partition(Container& container, int beg, int end, Comp&& comp)
{
    int lower = 0;
    int upper = 0;

    int i = beg - 1;
    int j = beg;
    auto piv = container[end - 1]; // take last element as pivot

    auto partition_helper = [&](auto piv_comp) {
        while (j < (end - 1)) {
            while (j < (end - 1) && !piv_comp(comp(container[j], piv), 0)) {
                ++j;
            }
            if (j < (end - 1)) {
                std::swap(container[j++], container[++i]);
            }
        }
    };

    auto less_than = [](const auto& x, const auto& y) {
        return x < y;
    };

    auto equal = [](const auto& x, const auto& y) {
        return x == y;
    };

    // Partition such that all elements < pivot is placed to the left
    partition_helper(less_than);
    lower = i + 1; // set upper bound for the lower part to recurse

    // Partition such that all elements == pivot is placed in the middle
    j = lower;
    partition_helper(equal);

    // Move pivot
    std::swap(container[++i], container[end - 1]);

    upper = i + 1; // set lower bound for the upper part to recurse

    return std::make_pair(lower, upper);
}

template <class Container, class Comp>
inline void qsort(Container& container, int beg, int end, Comp&& comp) 
{
    if (beg != end) {
        auto&& iters = partition(container, beg, end, std::forward<Comp>(comp));
        qsort(container, beg, std::get<0>(iters), std::forward<Comp>(comp));
        qsort(container, std::get<1>(iters), end, std::forward<Comp>(comp));
    } 
}

} // namespace details

template <class Container, class Comp = details::AscendingComp>
inline void qsort(const Container& source, Container& dest, Comp&& comp = Comp()) 
{
    dest = source;
    details::qsort(dest, 0, dest.size(), std::forward<Comp>(comp));
}

////////////////////////////////////////////////////////////////
// Counting Sort Implementation
////////////////////////////////////////////////////////////////

namespace details {

template <class Container>
void counting_sort(const Container& source, Container& dest)
{
    using value_type = typename Container::value_type;
    value_type max = *(std::max_element(source.begin(), source.end()));
    std::vector<value_type> counter(max + 1, 0);
    
    // count
    for (const auto& x : source) {
        ++(counter[x]);
    } 

    // accumulate counts
    for (size_t i = 1; i < counter.size(); ++i) {
        counter[i] += counter[i-1];
    }

    // fill container
    auto riter = source.rbegin();
    for (; riter != source.rend(); ++riter) {
        dest[--counter[*riter]] = *riter;
    }
}

} // namespace details

template <class Container>
inline void counting_sort(const Container& source, Container& dest)
{
    dest.resize(source.size());
    details::counting_sort(source, dest);
}


///////////////////////////////////////////////////////////////
// Lexicographical Sort
///////////////////////////////////////////////////////////////

namespace details {

template <class String>
constexpr inline size_t char_to_idx(const String& s, char base) {
    if (s.empty()) {
        return static_cast<size_t>(0);
    }
    return static_cast<size_t>(s[0] - base + 1);
}

} // namespace details

// Lexicographically sorts a container with strings.
// It is expected that every string is all lower-case.
// The string object must support operator[], which returns a char.
template <class Container>
void lexi_sort(const Container& source, Container& dest)
{
    if (source.size() <= 1) {
        dest = source;
        return;
    }

    static constexpr size_t NUMCHARS = 27; // including empty string
    std::array<char, NUMCHARS> counter;
    counter.fill(0);
    Container sort_by_first(source.size());

    for (auto it = source.begin(); it != source.end(); ++it) {
        ++counter[details::char_to_idx(*it, 'a')];
    }

    for (size_t i = 1; i < counter.size(); ++i) {
        counter[i] += counter[i-1];
    }

    for (auto it = source.rbegin(); it != source.rend(); ++it) {
        sort_by_first[--counter[details::char_to_idx(*it, 'a')]] = *it;
    }

    size_t i = 0;
    // copy over the empty strings first
    while (i < sort_by_first.size() && sort_by_first[i].empty()) {
        dest.emplace_back(sort_by_first[i]);
        ++i;
    }

    size_t j = i;

    while (j < sort_by_first.size()) {
        char curr_char = sort_by_first[i][0];
        while (++j < sort_by_first.size() && sort_by_first[j][0] == curr_char);

        // i points to first element starting with current char
        // j points to one past last element starting with current char
        Container to_sort_rest(j - i);
        for (size_t idx = 0; idx < j - i; ++idx) {
            // copy all strings starting with current char
            // remove the first char before assigning
            to_sort_rest[idx] = sort_by_first[i + idx].substr(1);
        }
        Container sorted_rest;
        // lexicographically sort this subset of strings starting with current char
        // store them in sorted_rest
        lexi_sort(to_sort_rest, sorted_rest);

        // emplace back in dest with sorted_rest with 
        for (auto& str : sorted_rest) {
            dest.emplace_back(std::move(str.insert(0, 1, curr_char)));
        }

        // update i and j
        i = j;
    }
}

} // namespace algos
