
find_program (GCR glib-compile-resources)
if (NOT GCR)
	message (FATAL_ERROR "glib-compile-resources not found.")
endif ()

set (GRESOURCE_C_FILE "${PROJECT_BINARY_DIR}/gresource.c")

add_custom_command(
	OUTPUT "${GRESOURCE_C_FILE}"
	DEPENDS "${PROJECT_SOURCE_DIR}/data/resource.gresource.xml"
	COMMAND ${GCR} --sourcedir="${PROJECT_SOURCE_DIR}/data/" --target="${GRESOURCE_C_FILE}" --generate-source "${PROJECT_SOURCE_DIR}/data/resource.gresource.xml"
)

add_custom_target (compile-gresources DEPENDS "${GRESOURCE_C_FILE}")
add_dependencies (${BIN_NAME} compile-gresources)
target_sources(${BIN_NAME} PRIVATE "${GRESOURCE_C_FILE}")