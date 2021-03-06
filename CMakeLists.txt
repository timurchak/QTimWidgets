cmake_minimum_required(VERSION 3.0)

project(QTimWidgets)
export(PACKAGE "qtimwidgets")
#version info
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 0)
set(${PROJECT_NAME}_PATCH_VERSION 2)
set(${PROJECT_NAME}_VERSION ${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_VERSION})

#project options
option(BUILD_DEB "will build debian package" ON)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})

#some packaging info

include(TConfigureTargetsExport)
include(TInstallShlib)
include(GNUInstallDirs)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(plnlog REQUIRED)
include(UseCxx11)
include(cleanSourceFiles)

use_cxx11()

include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}    
    ${CMAKE_CURRENT_SOURCE_DIR}/src/include
    ${QT_INCLUDES}
    ${${PROJECT_NAME}_OPT_INCLUDE_DIRS})

    chak_add_sources(PREFIX ${PROJECT_NAME}_QT
    HEADERS        

        src/include/qdynamicgridlayout.h
        src/include/qdoublescrollbar.h
        src/include/qdoubleslider.h
    SOURCES        
        src/qdynamicgridlayout.cpp
        src/qdoublescrollbar.cpp
        src/qdoubleslider.cpp
    )
    

    
add_definitions(${QT_DEFINITIONS}
${${PROJECT_NAME}_OPT_DEFINITIONS}
${CUSTOM_CXX_FLAGS})
    
if(UNIX)
    add_definitions(${CUSTOM_CXX_FLAGS})
endif(UNIX)
if(WIN32)
    set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} ${CUSTOM_CXX_FLAGS})
endif(WIN32)

set(TARGET_LIBRARY qtimwidgets)

qt5_wrap_cpp(${PROJECT_NAME}_MOCs ${${PROJECT_NAME}_QT_HEADERS})

add_library(${TARGET_LIBRARY} SHARED ${OS_EX_FLAG}
    ${${PROJECT_NAME}_QT_SOURCES}
    ${${PROJECT_NAME}_QT_HEADERS}
    ${${PROJECT_NAME}_UIs}
    ${${PROJECT_NAME}_MOCs}  
    ${${PROJECT_NAME}_VERSION_FILES})

target_include_directories(${TARGET_LIBRARY} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src/include>
    $<INSTALL_INTERFACE:include/${TARGET_LIBRARY}>)

#set_property(TARGET ${TARGET_LIBRARY} PROPERTY POSITION_INDEPENDENT_CODE ON)

t_debug("${PROJECT_NAME}_OPT_TARGET_OPTIONS = ${${PROJECT_NAME}_OPT_TARGET_OPTIONS}")

set_target_properties(${TARGET_LIBRARY}
    PROPERTIES
    VERSION ${${PROJECT_NAME}_VERSION}
    SOVERSION ${${PROJECT_NAME}_MAJOR_VERSION}
    LINKER_LANGUAGE "CXX"
    POSITION_INDEPENDENT_CODE ON
    EXPORT_NAME ${TARGET_LIBRARY}
    #PUBLIC_HEADER ${${PROJECT_NAME}_QT_HEADERS}
    ${${PROJECT_NAME}_OPT_TARGET_OPTIONS}
    )

set_property(TARGET ${TARGET_LIBRARY} PROPERTY PUBLIC_HEADER ${${PROJECT_NAME}_QT_HEADERS})

target_link_libraries(${TARGET_LIBRARY}
    ${QT_LIBRARIES}
    ${${PROJECT_NAME}_OPT_LIBS}
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui    
)

t_debug("CMAKE_INSTALL_LIBDIR = ${CMAKE_INSTALL_LIBDIR}")
t_debug("DESTINATION = ${CMAKE_INSTALL_INCLUDEDIR}/${TARGET_LIBRARY}")

t_shlib_install(TARGETS ${TARGET_LIBRARY}
    EXPORT ${TARGET_LIBRARY}Targets
    LIBRARY
    DESTINATION "${CMAKE_INSTALL_LIBDIR}"
    PUBLIC_HEADER
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${TARGET_LIBRARY}"
    COMPONENT dev)

install(FILES ${${PROJECT_NAME}_QT_HEADERS}
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/${TARGET_LIBRARY}"
    COMPONENT dev)

t_configure_targets_export(CONFIGURE_LIB CREATE_CONFIG CREATE_VERSION
    PACKAGE_NAME ${TARGET_LIBRARY}
    TARGETS_NAMES ${TARGET_LIBRARY}
    INSTALL_PREFIX "/usr"
    INSTALL_INCLUDES "${CMAKE_INSTALL_INCLUDEDIR}"
    BUILD_TREE_EXPORT_PATH "${CMAKE_BINARY_DIR}")

if(UNIX)
    if(BUILD_DEB)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postinst.in ${CMAKE_CURRENT_BINARY_DIR}/postinst @ONLY)
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postrm.in ${CMAKE_CURRENT_BINARY_DIR}/postrm @ONLY)
        set( CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA "${CMAKE_CURRENT_BINARY_DIR}/postinst;${CMAKE_CURRENT_BINARY_DIR}/postrm;" )
        message("building .deb package")
        #set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)
        set(CPACK_GENERATOR "DEB")
        SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "KK")
    endif(BUILD_DEB)
endif(UNIX)
include(CPackConfig.cmake)
include(CPack)
