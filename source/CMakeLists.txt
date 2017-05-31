
# Set up RCC
# Give directories that you know you need in runtime compilable classes
set( RCC_INCLUDE_DEPENDENCIES ${CMAKE_CURRENT_SOURCE_DIR} )
# Give the include directory for RCC to find definition of an IObject
set( IObject_INCLUDE ${CMAKE_CURRENT_SOURCE_DIR} )
# Give a semi-colon separated list of directories for searching for libraries
set( RCC_LIBRARY_DIRS )
# Build RCC
add_subdirectory( ${CMAKE_SOURCE_DIR}/extern/RunTimeCompiledCPlusPlus ${CMAKE_CURRENT_BINARY_DIR}/rcc )

# Set up the project target that uses RCC
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
