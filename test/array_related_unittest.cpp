#include "algorithms/array_related.hpp"
#include "gtest/gtest.h"
#include <vector>

namespace algos {

////////////////////////////////////////////////
// Linear Combination
////////////////////////////////////////////////

TEST(linear_combination, small_int_arrays_true) {
    std::vector<int> v1({0, 1, 2, 3, 4});
    std::vector<int> v2({5, 7, 9, 10, 31});
    bool res = linear_combination(v1, v2, 34);  
    EXPECT_TRUE(res);
}

TEST(linear_combination, small_int_arrays_false) {
    std::vector<int> v1({0, 1, 2, 3, 4});
    std::vector<int> v2({5, 7, 9, 10, 31});
    bool res = linear_combination(v1, v2, 11);  
    EXPECT_FALSE(res);
}

TEST(linear_combination, small_int_arrays_all_true) {
    std::vector<int> v1({0, 1, 2, 3, 4});
    std::vector<int> v2({5, 7, 9, 10, 31});
    for (size_t i = 0; i < v1.size(); ++i) {
        for (size_t j = 0; j < v2.size(); ++j) {
            bool res = linear_combination(v1, v2, 2*v1[i] + 3*v2[j]);  
            EXPECT_TRUE(res);
        }
    }
}

///////////////////////////////////////////////////////////////
// Maximum Subarray (Kadane)
///////////////////////////////////////////////////////////////
TEST(max_subarray, two_elements_all) {
    std::vector<int> v1({2, 4});
    int res = max_subarray(v1);
    EXPECT_EQ(res, 6);
}

TEST(max_subarray, two_elements_last) {
    std::vector<int> v1({-2, 4});
    int res = max_subarray(v1);
    EXPECT_EQ(res, 4);
}

TEST(max_subarray, many_elements_trapped) {
    std::vector<int> v1({-2, -2, 0, 100, 3, -203, 1, 40, 54});
    int res = max_subarray(v1);
    EXPECT_EQ(res, 103);
}

TEST(max_subarray, many_elements_overcome) {
    std::vector<int> v1({-1, 15, -2, 30});
    int res = max_subarray(v1);
    EXPECT_EQ(res, 43);
}

///////////////////////////////////////////////////////////////
// Maximum Subarray (Kadane)
///////////////////////////////////////////////////////////////
TEST(remove_dups, two_elements_same) {
    std::vector<int> v1({2, 2});
    int res = remove_dups(v1);
    EXPECT_EQ(res, 1);
    EXPECT_EQ(v1[0], 2);
}

TEST(remove_dups, two_elements_different) {
    std::vector<int> v1({-2, -1});
    int res = remove_dups(v1);
    EXPECT_EQ(res, 2);
    EXPECT_EQ(v1[0], -2);
    EXPECT_EQ(v1[1], -1);
}

TEST(remove_dups, many_elements) {
    std::vector<int> v1({-2, -1, 3, 4, 4, 4, 5, 7});
    std::vector<int> unique_vals({-2, -1, 3, 4, 5, 7});

    int res = remove_dups(v1);
    EXPECT_EQ(res, unique_vals.size());
    for (size_t i = 0; i < unique_vals.size(); ++i) {
        EXPECT_EQ(v1[i], unique_vals[i]);
    }
}

}
