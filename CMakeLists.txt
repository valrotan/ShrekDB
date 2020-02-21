cmake_minimum_required(VERSION 3.5)

project(22C_Final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file( GLOB UI_SOURCES 22C_FinalProject/src/ui/*.cpp )
file( GLOB UTIL_SOURCES 22C_FinalProject/src/util/*.cpp )

file( GLOB APP_SOURCES
	${UI_SOURCES}
	${UTIL_SOURCES}
)

file( GLOB TEST_SOURCES
	${APP_SOURCES}
)

add_executable( runFinal	22C_FinalProject/src/main.cpp ${APP_SOURCES} )
add_executable( runTest 22C_FinalProject/test/test.cpp ${TEST_SOURCES} )
