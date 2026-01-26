include(FetchContent)
enable_testing()

# Fetch GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(tests movavg_test.cpp)

target_link_libraries(tests
    libSMngr
    GTest::gtest
    GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests)
