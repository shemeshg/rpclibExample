set(serverBal_SRCS
    serverBal.cpp
    SessionStateItem.cpp
    CounterExampleServer.cpp 
    ServerBalSession.cpp

)

# Declare the library
add_library(serverBal STATIC
    ${serverBal_SRCS}
)

target_link_libraries(serverBal PRIVATE rpc libSMngr)

# Specify here the include directories exported
# by this library
target_include_directories(serverBal PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
