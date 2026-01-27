cmake_minimum_required(VERSION 3.14)
project(pyclient LANGUAGES CXX)

# Fetch pybind11 automatically
include(FetchContent)
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.12.0
)
FetchContent_MakeAvailable(pybind11)

# Create Python module
pybind11_add_module(pyclient pyclient.cpp)

target_link_libraries(pyclient PRIVATE clientBal serverBal libSMngr rpc)
