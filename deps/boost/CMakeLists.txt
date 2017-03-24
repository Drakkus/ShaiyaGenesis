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
if(WIN32)
 set(BOOST_DEBUG ON)
  if(DEFINED ENV{BOOST_ROOT})
    set(BOOST_ROOT $ENV{BOOST_ROOT})
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.0)
      set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib${PLATFORM}-msvc-12.0)
    else()
      set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib${PLATFORM}-msvc-14.0)
    endif()
  else()
    message(FATAL_ERROR "No BOOST_ROOT environment variable could be found! Please make sure it is set and the points to your Boost installation.")
  endif()

  set(Boost_USE_STATIC_LIBS        ON)
  set(Boost_USE_MULTITHREADED      ON)
  set(Boost_USE_STATIC_RUNTIME     OFF)
endif()

find_package(Boost 1.58 REQUIRED system filesystem thread program_options iostreams)

# Find if Boost was compiled in C++03 mode because it requires -DBOOST_NO_CXX11_SCOPED_ENUMS
include(CheckCXXSourceCompiles)

set(CMAKE_REQUIRED_INCLUDES ${Boost_INCLUDE_DIR})
set(CMAKE_REQUIRED_LIBRARIES ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_IOSTREAMS_LIBRARY})
set(CMAKE_REQUIRED_FLAGS "-std=c++11")
check_cxx_source_compiles("
  #include <boost/filesystem/path.hpp>
  #include <boost/filesystem/operations.hpp>
  int main() { boost::filesystem::copy_file(boost::filesystem::path(), boost::filesystem::path()); }"
boost_filesystem_copy_links_without_NO_SCOPED_ENUM)
unset(CMAKE_REQUIRED_INCLUDES)
unset(CMAKE_REQUIRED_LIBRARIES)
unset(CMAKE_REQUIRED_FLAGS)

add_library(boost INTERFACE)

target_link_libraries(boost
  INTERFACE
    ${Boost_LIBRARIES})

target_include_directories(boost
  INTERFACE
    ${Boost_INCLUDE_DIRS})

if (boost_filesystem_copy_links_without_NO_SCOPED_ENUM)
  target_compile_definitions(boost
    INTERFACE
      -DBOOST_DATE_TIME_NO_LIB
      -DBOOST_REGEX_NO_LIB
      -DBOOST_CHRONO_NO_LIB)
else()
  target_compile_definitions(boost
    INTERFACE
      -DBOOST_DATE_TIME_NO_LIB
      -DBOOST_REGEX_NO_LIB
      -DBOOST_CHRONO_NO_LIB
      -DBOOST_NO_CXX11_SCOPED_ENUMS)
endif()
