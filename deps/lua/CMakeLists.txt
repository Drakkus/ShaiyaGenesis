find_package(Lua 5.2 REQUIRED)

if(NOT LUA_FOUND)
  message(FATAL_ERROR "Lua wasn't found on your system but it's required to build the game servers=!")
endif()

add_library(lua STATIC IMPORTED GLOBAL)

set_target_properties(lua
  PROPERTIES
    IMPORTED_LOCATION
      "${LUA_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES
"${LUA_INCLUDE_DIR}")