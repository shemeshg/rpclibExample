include(FetchContent)
enable_testing()

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests BalTest.cpp)

target_link_libraries(tests
    serverBal
    clientBal
    rpc
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)


