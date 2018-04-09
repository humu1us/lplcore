cmake_minimum_required(VERSION 3.7.2)

project(lplcore)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../lib)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

if (${DEBUG} AND ${DEBUG} EQUAL 1)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif()

file(GLOB SOURCES src/*.c)
include_directories(include)

add_library(${PROJECT_NAME} SHARED ${SOURCES})

# Install library
install(TARGETS ${PROJECT_NAME} DESTINATION lib/)
file(GLOB HEADERS include/lplcore/*.h)
install(FILES ${HEADERS} DESTINATION include/${PROJECT_NAME})

# Test
enable_testing()
add_subdirectory(tests)
add_test(header_new tests/header_new)
add_test(search tests/search)
add_test(append tests/append)
add_test(delete tests/delete)
