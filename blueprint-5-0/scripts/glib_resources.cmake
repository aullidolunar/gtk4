# scripts
	
find_program(GLIB_COMPILE_RESOURCES_EXECUTABLE "glib-compile-resources" REQUIRED)

function(COMPILE_GLIB_RESOURCES _program_bin _xml_prefix _sources_lookup)
	set(DEPS "${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml")
	if (NOT "${ARGN}" STREQUAL "")
		set(DEPS ${DEPS} ${ARGN})
	endif()
	add_custom_command(
		OUTPUT
			"${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml.c"
		DEPENDS
			${DEPS}
		COMMAND
			${GLIB_COMPILE_RESOURCES_EXECUTABLE}
			--sourcedir=${_sources_lookup}
			--target=${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml.c
			--generate-source
			${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml
		VERBATIM
	)
		
	add_custom_target(
		compile-${_xml_prefix}-gresources
		DEPENDS
			"${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml.c"
		VERBATIM
	)
	
	target_sources(${_program_bin} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${_xml_prefix}.gresource.xml.c")
	add_dependencies(${_program_bin} compile-${_xml_prefix}-gresources)
endfunction()