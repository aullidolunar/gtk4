# data/win

string(REPLACE "." "," PROGRAM_VERSION_COMMA ${PROGRAM_VERSION})
string(REPLACE "%s" "${BUILD_SYS}" PROGRAM_DESCRIPTION ${PROGRAM_DESC})

target_include_directories(${BIN_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

configure_file(
	"resource.rc.in"
	"${CMAKE_CURRENT_BINARY_DIR}/resource.rc"
)

configure_file(
	"win.gresource.xml.in"
	"${CMAKE_CURRENT_BINARY_DIR}/win.gresource.xml"
)

target_sources(${BIN_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/resource.rc")

COMPILE_GLIB_RESOURCES(
	"${BIN_NAME}"
	"${DIR_NAME}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
)
