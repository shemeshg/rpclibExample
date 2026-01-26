set(Main_SRCS
    main.cpp
)

add_executable(movavg
    ${Main_SRCS}
)
target_link_libraries(movavg libSMngr)
 

install(TARGETS movavg DESTINATION bin)
