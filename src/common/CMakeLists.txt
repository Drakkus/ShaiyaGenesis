# Collect the source files to be compiled
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/ *.cpp *.h)

# Add an export definition
add_definitions(-DGENESIS_API_EXPORT_COMMON)

# Collect the include directories
collect_include_directories(${CMAKE_CURRENT_SOURCE_DIR} PUBLIC_INCLUDES)

# Add the library build target
add_library(common ${SRC})

# Define the common library to include the public sources
target_include_directories(common
  INTERFACE
    ${PUBLIC_INCLUDES})
	
# Define the linking language
set_target_properties(common PROPERTIES LINKER_LANGUAGE CXX)

# Link the library
target_link_libraries(common
	PUBLIC
		boost)