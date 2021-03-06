cmake_minimum_required( VERSION 3.0.0 )
project( CrystalLib )

### Options
option ( BUILD_TEST "Build test project" ON )


### Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/arch")

### Compilation configuration ###
if(MSVC)
    ### Enable parallel compilation for Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP /bigobj")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /w") # disable all warnings (not ideal but...)
else()
    #### Libigl requires a modern C++ compiler that supports c++11
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w") # disable all warnings (not ideal but...)
endif()



### Set enviroments variables
set( CRYSTALLIB               "${PROJECT_NAME}" )
set( CRYSTALLIB_ROOT          "${PROJECT_SOURCE_DIR}" )
set( CRYSTALLIB_INCLUDE_DIRS  "${PROJECT_SOURCE_DIR}/include" )
set( CRYSTALLIB_DEFINITIONS   "" )
set( CRYSTALLIB_EXTRA_LIBS    "" )

### Third party Find?.CMake
set( CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/FindCMake" )

### Third party find manualy
set( LIBIGL_INCLUDE "LIBIGL_INCLUDE NOT FOUND" CACHE PATH "Include dir of libigl" )
#FILEPATH

### Third party dependency
find_package( Eigen3  REQUIRED )
find_package( OpenCV  REQUIRED )
list( APPEND CRYSTALLIB_INCLUDE_DIRS  "${EIGEN3_INCLUDE_DIR}" )
list( APPEND CRYSTALLIB_INCLUDE_DIRS  "${OpenCV_INCLUDE_DIRS}" )
list( APPEND CRYSTALLIB_INCLUDE_DIRS  "${LIBIGL_INCLUDE}" )
list( APPEND CRYSTALLIB_EXTRA_LIBS    "${OpenCV_LIBS}" )

# Build CrystalLib
set( CRYSTALLIB_SOURCE_FILES "src/CrystalLib.cpp" )

include_directories( ${CRYSTALLIB_INCLUDE_DIRS} )
add_definitions( ${CRYSTALLIB_DEFINITIONS} )
add_library( ${PROJECT_NAME} SHARED ${CRYSTALLIB_SOURCE_FILES} )
target_link_libraries( ${PROJECT_NAME} ${CRYSTALLIB_EXTRA_LIBS} )


if ( BUILD_TEST )
    add_subdirectory( "${PROJECT_SOURCE_DIR}/CryTest" "CryTest" )
endif (BUILD_TEST)