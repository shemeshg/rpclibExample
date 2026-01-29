cmake_minimum_required(VERSION 3.10)
project(rpclibExample LANGUAGES C CXX)
set(CMAKE_CXX_STANDARD 20)
enable_testing()

include(FetchContent)

FetchContent_Declare(
  rpclib
  GIT_REPOSITORY https://github.com/rpclib/rpclib.git
  GIT_TAG v2.3.0
)

FetchContent_MakeAvailable(rpclib)

add_subdirectory(pyclient)
add_subdirectory(clientBal)
add_subdirectory(serverBal)
add_subdirectory(test)

# Server
add_executable(server
    server.cc
)

target_link_libraries(server PRIVATE rpc serverBal )

# Client
add_executable(client
    client.cc
)

target_link_libraries(client PRIVATE clientBal rpc)
