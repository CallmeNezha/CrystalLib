cmake_minimum_required( VERSION 3.0.0 )
project( CryTest )

### Compilation configuration ###
if(MSVC)
    ### Enable parallel compilation for Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj")
else()
    #### Libigl requires a modern C++ compiler that supports c++11
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_executable( ${PROJECT_NAME} main.cpp )

target_include_directories( ${PROJECT_NAME} PRIVATE ${CRYSTALLIB_INCLUDE_DIRS} )
target_compile_definitions( ${PROJECT_NAME} PRIVATE ${CRYSTALLIB_DEFINITIONS} )
target_link_libraries( ${PROJECT_NAME} ${CRYSTALLIB} )