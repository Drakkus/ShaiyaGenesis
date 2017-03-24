# Collect the source files to be compiled
file(GLOB_RECURSE SRC RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/ *.cpp *.h)

# Add an export definition
add_definitions(-DGENESIS_API_EXPORT_DBSERVER)

# Collect the include directories
collect_include_directories(${CMAKE_CURRENT_SOURCE_DIR} PUBLIC_INCLUDES)
  
# Provide an interface target for the update server project to allow
# dependent projects to build meanwhile.
add_library(dbserver-interface INTERFACE)

# Define the update server interface library to include the public sources
target_include_directories(dbserver-interface
  INTERFACE
    ${PUBLIC_INCLUDES})
	
# Add the library build target
add_executable(db_server ${SRC})

# Define the linking language
set_target_properties(db_server PROPERTIES LINKER_LANGUAGE CXX)

# Link the library
target_link_libraries(db_server
	PUBLIC
		dbserver-interface
		common
		mysql)