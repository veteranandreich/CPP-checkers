project(game)

set(SOURCES
		checker_game.cpp)
set(HEADERS
		game.h
		structures.h
		checker_game.h)

include_directories(../)

add_library(game ${SOURCES} ${HEADERS})
