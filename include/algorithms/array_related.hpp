#pragma once
#include <type_traits>
#include <cassert>
#include <limits>
#include <algorithm>

namespace algos {

// The arrays must be sorted in increasing order.
template <class A1, class A2>
bool linear_combination(A1 const& arr1, A2 const& arr2, typename A1::value_type c)
{
    static_assert(std::is_same<typename A1::value_type, typename A2::value_type>::value);
    using value_type = typename A1::value_type;

    assert(arr1.size() == arr2.size());
    size_t i = 0;
    int j = arr1.size() - 1;
    while (i < arr1.size() && j >= 0) {
        value_type lin_comb = 2*arr1[i] + 3*arr2[j];
        if (lin_comb == c) {
            return true;
        }
        else if (lin_comb < c) {
            ++i;
        }
        else {
            --j;
        }
    }

    return false;
}

///////////////////////////////////////////////////////////////
// Maximum Subarray (Kadane)
///////////////////////////////////////////////////////////////
template <class Container>
typename Container::value_type max_subarray(const Container& v)
{
    using value_type = typename Container::value_type;
    value_type max_sum_up_to = std::numeric_limits<value_type>::min();
    value_type max_sum = std::numeric_limits<value_type>::min();
    for (const auto& x : v) {
        max_sum_up_to = x + std::max(0, max_sum_up_to);
        max_sum = std::max(max_sum, max_sum_up_to);
    }
    return max_sum;
}

///////////////////////////////////////////////////////////////
// Remove duplicates from int array 
///////////////////////////////////////////////////////////////
// Modifies the array such that if there are k unique integers in array arr
// the first k elements of arr will contain these unique integers.
// arr is assumed to be sorted.
// The k unique integers is guaranteed to be sorted.
// Returns k
template <class Container>
size_t remove_dups(Container& arr)
{
    if (arr.size() <= 1) {
        return arr.size();
    }

    size_t i = 0;
    size_t j = i + 1;

    while (j < arr.size())
    {
        while (j < arr.size() && arr[j] == arr[i]) {
            ++j;
        }

        if (j == arr.size()) {
            break;
        }

        ++i;
        std::swap(arr[i], arr[j]);
        ++j;
    }

    return i + 1;
}

} // namespace algos
