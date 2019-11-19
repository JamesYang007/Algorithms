set(GTEST_DIR "${PROJECT_SOURCE_DIR}/googletest/googletest")

add_compile_options(-pthread -isystem ${GTEST_DIR}/include)

set(
    UNITTESTS
    array_related_unittest
    sort_unittest
)

add_library(gtest_main.a STATIC ${GTEST_DIR}/src/gtest-all.cc ${GTEST_DIR}/src/gtest_main.cc)
target_include_directories(gtest_main.a PRIVATE ${GTEST_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include)

foreach( test ${UNITTESTS} )
    add_executable(${test} ${CMAKE_CURRENT_SOURCE_DIR}/${test}.cpp)
    target_link_libraries(${test} gtest_main.a)
    add_test(${test} ${test})
endforeach()
