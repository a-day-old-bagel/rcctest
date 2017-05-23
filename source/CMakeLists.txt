
# Use RCC

# Get all include directories for this project and pass them to RCC.
# Alternatively you can only include the directories that you know you need in runtime compilable classes
get_property( RCC_INCLUDE_DEPENDENCIES DIRECTORY PROPERTY INCLUDE_DIRECTORIES )

# Set the include directory for RCC to find definition of an IObject
set( IObject_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} )

# Semi-colon separated list of directories for searching for libraries
set( RCC_LIBRARY_DIRS )

# Add this to project to gain access to the object factory system
#add_subdirectory( "RCC" )

add_subdirectory( ${CMAKE_SOURCE_DIR}/extern/RunTimeCompiledCPlusPlus ${CMAKE_CURRENT_BINARY_DIR}/rcc )

include_directories( ${RCC_INCLUDE_DIRS} )



set( TARGET_NAME rccptest )
add_executable( ${TARGET_NAME}
    main.cpp
    )
target_link_libraries( rccptest
    RuntimeCompiler
    RuntimeObjectSystem
    )
set_property( TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD 14 )
set_property( TARGET ${TARGET_NAME} PROPERTY CXX_STANDARD_REQUIRED ON )
