# data

find_program (GCR "glib-compile-resources" NO_CACHE)

if (NOT GCR)
	message (FATAL_ERROR "glib-compile-resources no fue encontrado.")
else()
	message ("glib-compile-resources: ${GCR}")
	add_custom_command (
		OUTPUT "${CMAKE_BINARY_DIR}/resources.c"
		DEPENDS "${PROJECT_SOURCE_DIR}/data/resources.gresource.xml"
		COMMAND ${GCR} --sourcedir="${PROJECT_SOURCE_DIR}/data" --target="${CMAKE_BINARY_DIR}/resources.c" --generate-source "${PROJECT_SOURCE_DIR}/data/resources.gresource.xml"
	)
	add_custom_target (compile-resources DEPENDS "${CMAKE_BINARY_DIR}/resources.c")
	add_dependencies (${BIN_NAME} compile-resources)
	target_sources (${BIN_NAME} PRIVATE "${CMAKE_BINARY_DIR}/resources.c")
endif ()

