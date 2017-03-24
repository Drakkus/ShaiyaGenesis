# CMake >= 3.0 is required
cmake_minimum_required(VERSION 3.0)

# Set the project name
project(ShaiyaGenesis)

# Define the output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/out)

# Disable in-source builds
set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

# Set macro directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/macros")

# Build in Release-mode by default if not explicitly set
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

# Set default buildoptions and print them
include(cmake/options.cmake)

# Include the macros to use
include(check_platform)
include(auto_collect)
include(find_boost)
include(group_sources)

# Print out the results before continuing
include(cmake/show_options.cmake)

# Find the MySQL libraries
find_package(MySQL)

# Add dependencies
add_subdirectory(deps)

# Add core sources
add_subdirectory(src)