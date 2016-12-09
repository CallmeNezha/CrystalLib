cmake_minimum_required( VERSION 3.0.0 )
project( CryTest )

add_executable( ${PROJECT_NAME} main.cpp )

target_include_directories( ${PROJECT_NAME} PRIVATE ${CRYSTALLIB_INCLUDE_DIRS} )
target_compile_definitions( ${PROJECT_NAME} PRIVATE ${CRYSTALLIB_DEFINITIONS} )
target_link_libraries( ${PROJECT_NAME} ${CRYSTALLIB} )