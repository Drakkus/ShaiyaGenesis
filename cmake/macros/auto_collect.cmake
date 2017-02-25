# Copyright (C) 2016 Shaiya Genesis <http://www.shaiyagenesis.com/>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.
#
# Use it like:
# CollectSourceFiles(
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   COMMON_PRIVATE_SOURCES
#   # Exclude
#   ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders
#   ${CMAKE_CURRENT_SOURCE_DIR}/Platform)
#
function(collect_source_files current_dir variable)
  list(FIND ARGN "${current_dir}" IS_EXCLUDED)
  if(IS_EXCLUDED EQUAL -1)
    file(GLOB COLLECTED_SOURCES
      ${current_dir}/*.c
      ${current_dir}/*.cc
      ${current_dir}/*.cpp
      ${current_dir}/*.inl
      ${current_dir}/*.def
      ${current_dir}/*.h
      ${current_dir}/*.hh
      ${current_dir}/*.hpp)
    list(APPEND ${variable} ${COLLECTED_SOURCES})

    file(GLOB SUB_DIRECTORIES ${current_dir}/*)
    foreach(SUB_DIRECTORY ${SUB_DIRECTORIES})
      if (IS_DIRECTORY ${SUB_DIRECTORY})
        collect_source_files("${SUB_DIRECTORY}" "${variable}" "${ARGN}")
      endif()
    endforeach()
    set(${variable} ${${variable}} PARENT_SCOPE)
  endif()
endfunction()

# Collects all subdirectoroies into the given variable,
# which is useful to include all subdirectories.
# Ignores full qualified directories listed in the variadic arguments.
#
# Use it like:
# CollectIncludeDirectories(
#   ${CMAKE_CURRENT_SOURCE_DIR}
#   COMMON_PUBLIC_INCLUDES
#   # Exclude
#   ${CMAKE_CURRENT_SOURCE_DIR}/PrecompiledHeaders
#   ${CMAKE_CURRENT_SOURCE_DIR}/Platform)
#
function(collect_include_directories current_dir variable)
  list(FIND ARGN "${current_dir}" IS_EXCLUDED)
  if(IS_EXCLUDED EQUAL -1)
    list(APPEND ${variable} ${current_dir})
    file(GLOB SUB_DIRECTORIES ${current_dir}/*)
    foreach(SUB_DIRECTORY ${SUB_DIRECTORIES})
      if (IS_DIRECTORY ${SUB_DIRECTORY})
        collect_include_directories("${SUB_DIRECTORY}" "${variable}" "${ARGN}")
      endif()
    endforeach()
    set(${variable} ${${variable}} PARENT_SCOPE)
  endif()
endfunction()