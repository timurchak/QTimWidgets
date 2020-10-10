 # - use cpp11 standart all version cmake
 # Usage:
 #  use_cxx11()
 #
 macro(use_cxx11)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++11")
      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++14")
#      set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=gnu++17")
    endif ()
  else ()
    set (CMAKE_CXX_STANDARD 11)
    set (CMAKE_CXX_STANDARD 14)
#    set (CMAKE_CXX_STANDARD 17)
  endif ()
endmacro(use_cxx11)
