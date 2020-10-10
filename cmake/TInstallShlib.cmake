include(TUtils)
include(CMakePackageConfigHelpers)
macro(t_shlib_install)    
    set(oneValueArgs EXPORT)
    set(multiValueArgs TARGETS ARCHIVE LIBRARY RUNTIME FRAMEWORK BUNDLE PRIVATE_HEADER PUBLIC_HEADER RESOURCE)

    cmake_parse_arguments(CFG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    t_check_param(CFG_TARGETS "TARGETS" "t_shlib_install")
    t_check_param(CFG_EXPORT "EXPORT" "t_shlib_install")
    t_check_param(CFG_LIBRARY "LIBRARY" "t_shlib_install")

    t_debug("t_shlib_install: got LIBRARY = ${CFG_LIBRARY}")
    t_debug("t_shlib_install: got TARGETS = ${CFG_TARGETS}")
    t_debug("t_shlib_install: got EXPORT = ${CFG_EXPORT}")


    set(LIBRARY_oneValueArgs DESTINATION COMPONENT COMPONENT_DEV)

    cmake_parse_arguments(LIBRARY_CFG "${LIBRARY_optionsLib}" "${LIBRARY_oneValueArgs}" "${LIBRARY_multiValueArgs}" ${CFG_LIBRARY})

    t_check_param(LIBRARY_CFG_DESTINATION "DESTINATION" "t_shlib_install")


    if(NOT DEFINED LIBRARY_CFG_COMPONENT)
        set(LIBRARY_CFG_COMPONENT "shlib")
    endif(NOT DEFINED LIBRARY_CFG_COMPONENT)

    if(NOT DEFINED LIBRARY_CFG_COMPONENT_DEV)
        set(LIBRARY_CFG_COMPONENT_DEV "dev")
    endif(NOT DEFINED LIBRARY_CFG_COMPONENT_DEV)

    t_debug("t_shlib_install: CFG_TARGETS = ${CFG_TARGETS}")
    t_debug("t_shlib_install: CFG_EXPORT = ${CFG_EXPORT}")
    t_debug("t_shlib_install: LIBRARY_CFG_DESTINATION = ${LIBRARY_CFG_DESTINATION}")
    t_debug("t_shlib_install: LIBRARY_CFG_COMPONENT = ${LIBRARY_CFG_COMPONENT}")
    t_debug("t_shlib_install: LIBRARY_CFG_COMPONENT_DEV = ${LIBRARY_CFG_COMPONENT_DEV}")
    t_debug("t_shlib_install: CFG_ARCHIVE = ${CFG_ARCHIVE}")
    t_debug("t_shlib_install: CFG_RUNTIME = ${CFG_RUNTIME}")
    t_debug("t_shlib_install: CFG_FRAMEWORK = ${CFG_FRAMEWORK}")
    t_debug("t_shlib_install: CFG_BUNDLE = ${CFG_BUNDLE}")
    t_debug("t_shlib_install: CFG_PRIVATE_HEADER = ${CFG_PRIVATE_HEADER}")
    t_debug("t_shlib_install: CFG_PUBLIC_HEADER = ${CFG_PUBLIC_HEADER}")
    t_debug("t_shlib_install: CFG_RESOURCE = ${CFG_RESOURCE}")
    #t_debug("t_shlib_install: CFG_BUNDLE = ${CFG_BUNDLE}")


    install(TARGETS ${CFG_TARGETS}
        EXPORT ${CFG_EXPORT}
        LIBRARY
        DESTINATION "${LIBRARY_CFG_DESTINATION}"
        COMPONENT "${LIBRARY_CFG_COMPONENT}"
        NAMELINK_SKIP
        ARCHIVE ${CFG_ARCHIVE}
        RUNTIME ${CFG_RUNTIME}
        FRAMEWORK ${CFG_FRAMEWORK}
        BUNDLE ${CFG_BUNDLE}
        PRIVATE_HEADER ${CFG_PRIVATE_HEADER}
        PUBLIC_HEADER ${CFG_PUBLIC_HEADER}
        RESOURCE ${CFG_RESOURCE})

    install(TARGETS ${CFG_TARGETS}
        EXPORT ${CFG_EXPORT}
        LIBRARY
        DESTINATION "${LIBRARY_CFG_DESTINATION}"
        COMPONENT "${LIBRARY_CFG_COMPONENT_DEV}"
        NAMELINK_ONLY)
    
endmacro(t_shlib_install)
