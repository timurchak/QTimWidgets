macro(chak_add_sources)
    set(oneValueArgs PREFIX)
    set(multiValueArgs HEADERS SOURCES)

    cmake_parse_arguments(PPARAM "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(${PPARAM_PREFIX}_HEADERS
        ${PPARAM_HEADERS})

    set(${PPARAM_PREFIX}_SOURCES
        ${PPARAM_SOURCES})

    if(${CMAKE_VERSION} VERSION_GREATER "3.8.2")
        source_group("" FILES ${${PPARAM_PREFIX}_SOURCES} ${${PPARAM_PREFIX}_HEADERS})
    endif(${CMAKE_VERSION} VERSION_GREATER "3.8.2")

endmacro(chak_add_sources)
