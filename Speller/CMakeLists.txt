cmake_minimum_required(VERSION 3.10)
project(Speller)

macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        message(STATUS "${_variableName}=${${_variableName}}")
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror -o2")
set(CMAKE_CXX_STANDARD 11)

add_executable(speller main.cpp ../HashTable/HashTable.cpp)

target_include_directories(speller PUBLIC
    ${Boost_INCLUDE_DIRS}
    ../UnorderedBinaryTree
    ../HashTable
    ../Trie
)

#find_package( Threads )
find_package( Boost COMPONENTS filesystem  REQUIRED )

#message(STATUS "Boost Libraries: " ${Boost_LIBRARIES} )

set( SANITIZES -fsanitize=address,undefined )

set( LIBS_TO_LINK
    ${Boost_LIBRARIES}
  #  ${CMAKE_THREAD_LIBS_INIT}
)

target_link_libraries (speller ${LIBS_TO_LINK} ${SANITIZES})