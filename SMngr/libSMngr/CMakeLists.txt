find_package(Boost CONFIG REQUIRED)

set(libSMngr_SRCS
    libSMngr.h
    libSMngr.cpp
)

# Declare the library
add_library(libSMngr STATIC
    ${libSMngr_SRCS}
)

# Specify here the include directories exported
# by this library
target_include_directories(libSMngr PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(libSMngr PRIVATE Boost::boost)



