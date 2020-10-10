include (CMakeParseArguments)

set (GeneratePKGCCurrentDir ${CMAKE_CURRENT_LIST_DIR})

function(generate_deb)
    #set (oneValueArgs
       # PREFIX
        #EXEC_PREFIX
        #LIBDIR
        #INCLUDEDIR
        #AME
        #ESCRIPTION
        #VERSION
        #LIBS
        #LIBS_PRIVATE
        #CFLAGS)
    #set (multiValueArgs)
    
    #cmake_parse_arguments(PRODUCT "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})
    
	message("generating .deb")
	get_filename_component(source_dir_name ${CMAKE_CURRENT_SOURCE_DIR} NAME)
	EXECUTE_PROCESS(COMMAND tar -zcf ${CMAKE_CURRENT_BINARY_DIR}/${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}.orig.tar.gz --exclude=Makefile --exclude=.hg --exclude=doc -C ${CMAKE_CURRENT_SOURCE_DIR} ../${source_dir_name} OUTPUT_VARIABLE GCC_VERSION_OUTPUT)
	EXECUTE_PROCESS(COMMAND tar xf ${CMAKE_CURRENT_BINARY_DIR}/${CPACK_PACKAGE_NAME}_${CPACK_PACKAGE_VERSION}.orig.tar.gz)
	set(UNPACKED_SOURCE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${source_dir_name})
	set(DEB_PKG_DIR ${UNPACKED_SOURCE_DIR}_deb)
	EXECUTE_PROCESS(COMMAND mv ${CMAKE_CURRENT_BINARY_DIR}/${source_dir_name} ${DEB_PKG_DIR})
	set(DEB_DIR ${DEB_PKG_DIR}/debian)
	EXECUTE_PROCESS(COMMAND mkdir -p ${DEB_DIR})
	configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/control.in
            ${DEB_DIR}/control
            @ONLY)
	EXECUTE_PROCESS(COMMAND dch --create -v ${CPACK_PACKAGE_VERSION}-${DEB_PKG_VERSION} --package ${CPACK_PACKAGE_NAME} "dummy" -M
			WORKING_DIRECTORY ${DEB_PKG_DIR})
	EXECUTE_PROCESS(COMMAND touch ${DEB_DIR}/copyright)
	configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/rules.in
            ${DEB_DIR}/rules
            @ONLY)
	configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/compat.in
            ${DEB_DIR}/compat
            @ONLY)
	configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postinst.in
            ${DEB_DIR}/postinst
            @ONLY)
	configure_file(
            ${CMAKE_CURRENT_SOURCE_DIR}/cmake/debian/postrm.in
            ${DEB_DIR}/postrm
            @ONLY)
    
endfunction()