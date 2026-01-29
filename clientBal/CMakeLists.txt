set(clientBal_SRCS
    clientBal.cpp
)

# Declare the library
add_library(clientBal STATIC
    ${clientBal_SRCS}
)

target_link_libraries(clientBal PRIVATE rpc)

# Specify here the include directories exported
# by this library
target_include_directories(clientBal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(clientBal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../sharedConst 
)