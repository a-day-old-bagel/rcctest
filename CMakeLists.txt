
cmake_minimum_required( VERSION 3.6 FATAL_ERROR)
set( CMAKE_DISABLE_IN_SOURCE_BUILD ON )
set( CMAKE_DISABLE_SOURCE_CHANGES ON )
project( rcctest VERSION 0.01.01.01 LANGUAGES CXX)

# Runtime Compiled C++ stuff
#add_subdirectory( "./extern/RunTimeCompiledCPlusPlus" )

add_subdirectory( "./source" )
