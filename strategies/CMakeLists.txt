project(strategies)
set(SOURCES
		human.cpp
        computer1.cpp
		computer_interface.cpp
		computer2.cpp)
set(HEADERS
		human.h
        computer1.h
		interface.h
		computer_interface.h
		computer2.h)

include_directories(../)

add_library(strategies ${SOURCES} ${HEADERS})
