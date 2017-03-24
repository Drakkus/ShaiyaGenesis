if(NOT MYSQLCONNECTORCPP_FOUND)
  message(FATAL_ERROR "MySQL wasn't found on your system but it's required to build the servers!")
endif()

add_library(mysql STATIC IMPORTED GLOBAL)

set_target_properties(mysql
  PROPERTIES
    IMPORTED_LOCATION
      "${MYSQLCONNECTORCPP_LIBRARIES}"
    INTERFACE_INCLUDE_DIRECTORIES
"${MYSQLCONNECTORCPP_INCLUDE_DIRS}")