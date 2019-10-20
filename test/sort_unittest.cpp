#include "algorithms/sort.hpp"
#include "gtest/gtest.h"
#include <vector>
#include <cassert>

namespace algos {

//////////////////////////////////////////////////////
// Quicksort
//////////////////////////////////////////////////////

TEST(qsort, one_element_sort) {
    std::vector<int> v1({1});
    std::vector<int> v2;
    qsort(v1, v2); 
    EXPECT_EQ(v2[0], 1);
}

TEST(qsort, two_element_sort) {
    std::vector<int> v1({5, 3});
    std::vector<int> v2;
    qsort(v1, v2); 
    EXPECT_EQ(v2[0], 3);
    EXPECT_EQ(v2[1], 5);
}

TEST(qsort, two_same_element_sort) {
    std::vector<int> v1({3, 3});
    std::vector<int> v2;
    qsort(v1, v2); 
    EXPECT_EQ(v2[0], 3);
    EXPECT_EQ(v2[1], 3);
}

TEST(qsort, three_element_sort) {
    std::vector<int> v1({2, -1, 3, 2});
    std::vector<int> v2;
    qsort(v1, v2); 
    EXPECT_EQ(v2[0], -1);
    EXPECT_EQ(v2[1], 2);
    EXPECT_EQ(v2[2], 2);
    EXPECT_EQ(v2[3], 3);
}

TEST(qsort, many_element_sort) {
    std::vector<int> v1({-4, 9, 10, 32, 1, 2, 3, 1, 2, 1, 0, 8, 6, 7});
    std::vector<int> v2;
    std::vector<int> sorted({-4, 0, 1, 1, 1, 2, 2, 3, 6, 7, 8, 9, 10, 32});

    assert(v1.size() == sorted.size());

    qsort(v1, v2); 

    for (int i = 0; i < sorted.size(); ++i) {
        EXPECT_EQ(sorted[i], v2[i]);
    }
}

//////////////////////////////////////////////////////
// Counting Sort
//////////////////////////////////////////////////////

TEST(counting_sort, many_element_sort) {
    std::vector<int> v1({5, 3, 2, 1, 4, 2, 10, 0});
    std::vector<int> v2;
    std::vector<int> sorted;

    qsort(v1, sorted);
    counting_sort(v1, v2);

    assert(v2.size() == sorted.size());

    for (int i = 0; i < v2.size(); ++i) {
        EXPECT_EQ(v2[i], sorted[i]);
    }
}

//////////////////////////////////////////////////////
// Lexicographical Sort
//////////////////////////////////////////////////////

TEST(lexi_sort, two_element_sort) {
    std::vector<std::string> v1({"a", ""});
    std::vector<std::string> v2;
    lexi_sort(v1, v2);
    EXPECT_EQ(std::string(""), v2[0]);
    EXPECT_EQ(std::string("a"), v2[1]);
}

TEST(lexi_sort, four_element_sort) {
    std::vector<std::string> v1({"b", "ba", "a", "bc"});
    std::vector<std::string> v2;
    lexi_sort(v1, v2);
    EXPECT_EQ(std::string("a"), v2[0]);
    EXPECT_EQ(std::string("b"), v2[1]);
    EXPECT_EQ(std::string("ba"), v2[2]);
    EXPECT_EQ(std::string("bc"), v2[3]);
}

TEST(lexi_sort, many_element_sort) {
    std::vector<std::string> v1({"cb","dba", "ec", "acc", "acb", "cab", "", "ba", "a", "bc"});
    std::vector<std::string> v2;
    lexi_sort(v1, v2);
    EXPECT_EQ(std::string(""), v2[0]);
    EXPECT_EQ(std::string("a"), v2[1]);
    EXPECT_EQ(std::string("acb"), v2[2]);
    EXPECT_EQ(std::string("acc"), v2[3]);
    EXPECT_EQ(std::string("ba"), v2[4]);
    EXPECT_EQ(std::string("bc"), v2[5]);
    EXPECT_EQ(std::string("cab"), v2[6]);
    EXPECT_EQ(std::string("cb"), v2[7]);
    EXPECT_EQ(std::string("dba"), v2[8]);
    EXPECT_EQ(std::string("ec"), v2[9]);
}

}
