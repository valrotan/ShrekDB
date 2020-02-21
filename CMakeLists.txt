cmake_minimum_required(VERSION 3.5)

project(final LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


file( GLOB UI_SOURCES 22C_FinalProject/src/ui/*.cpp )
file( GLOB UTIL_SOURCES 22C_FinalProject/src/util/*.cpp )

file( GLOB APP_SOURCES 
	22C_FinalProject/src/main.cpp
	${UI_SOURCES}
	${UTIL_SOURCES}
)

file( GLOB APP_SOURCES 
	22C_FinalProject/test/test.cpp
	${APP_SOURES}
)

add_executable( final ${APP_SOURCES} )
add_executable( test ${TEST_SOURCES} )
