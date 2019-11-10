set(GTEST_PATH "~/googletest/googletest")

include_directories(
    "${GTEST_PATH}/include"
    "${CMAKE_SOURCE_DIR}/include"
    )

add_executable(sort_unittest sort_unittest.cpp)
target_link_libraries(sort_unittest "${GTEST_PATH}/make/gtest_main.a")
