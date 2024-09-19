# data

include(../scripts/glib_resources.cmake)

find_program(BLUEPRINT_EXECUTABLE "blueprint-compiler" REQUIRED)

if (WIN32)
	set(BLUEPRINT_EXECUTABLE Python3::Interpreter ${BLUEPRINT_EXECUTABLE})
endif()

configure_file(
	"builder.blp.in"
	"${CMAKE_CURRENT_BINARY_DIR}/builder.blp"
)

add_custom_command(
	OUTPUT
		"${CMAKE_CURRENT_BINARY_DIR}/builder.glade"
	DEPENDS
		"${CMAKE_CURRENT_BINARY_DIR}/builder.blp"
	COMMAND
		${BLUEPRINT_EXECUTABLE}
		compile
		--output
		${CMAKE_CURRENT_BINARY_DIR}/builder.glade
		${CMAKE_CURRENT_BINARY_DIR}/builder.blp
	VERBATIM
)

set(I18N_SOURCES ${I18N_SOURCES} builder.glade PARENT_SCOPE)
set(GLADE_PATH ${CMAKE_CURRENT_BINARY_DIR})
set(GLADE_FILE "builder.glade")

set(UI_RESOURCE_PATH "${PROGRAM_RESOURCE_PATH}/builder.glade")
target_compile_definitions(${BIN_NAME} PRIVATE
	UI_RESOURCE_PATH="${UI_RESOURCE_PATH}"
)

configure_file(
	"main.gresource.xml.in"
	"${CMAKE_CURRENT_BINARY_DIR}/main.gresource.xml"
)

set(DIR_NAME "main")

COMPILE_GLIB_RESOURCES(
	"${BIN_NAME}"
	"${DIR_NAME}"
	"${CMAKE_CURRENT_SOURCE_DIR}"
	"${CMAKE_CURRENT_BINARY_DIR}/builder.glade"
)

if (WIN32)
	set(DIR_NAME "win")
else()
	set(DIR_NAME "unix")
endif()

set(DATA_SOURCES "${CMAKE_CURRENT_BINARY_DIR}/builder.glade")
add_subdirectory(${DIR_NAME})
foreach(dat_src ${DATA_SOURCES})
	list(APPEND I18N_SOURCES ${dat_src})
endforeach()
set(I18N_SOURCES ${I18N_SOURCES} PARENT_SCOPE)
