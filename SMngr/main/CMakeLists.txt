set(Main_SRCS
    main.cpp
)

add_executable(SMngr
    ${Main_SRCS}
)
target_link_libraries(SMngr libSMngr)
 

install(TARGETS SMngr DESTINATION bin)
