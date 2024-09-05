# data

find_program(blueprint_executable "blueprint-compiler" REQUIRED)
if (WIN32)
	find_package(Python3 REQUIRED)
	set(blueprint_executable Python3::Interpreter ${blueprint_executable})
endif()

find_program(gcr_executable "glib-compile-resources" REQUIRED)

set(GLADE_FILE "builder.glade")
set(PROJECT_DATA_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

string(REPLACE "." "/" PROGRAM_ID_BAR ${PROGRAM_ID})
set(PROGRAM_RESOURCE_PATH "/${PROGRAM_ID_BAR}")
set(ui_resource_path "${PROGRAM_RESOURCE_PATH}/${GLADE_FILE}")

set(MAIN_GRESOURCE_C "main.gresource.c")
set(PLATFORM_GRESOURCE_XML "platform.gresource.xml")
set(PLATFORM_GRESOURCE_C "platform.gresource.c")

set(DESKTOP_FILE "${PROJECT_NAME}.desktop.in" PARENT_SCOPE)

configure_file(
	"builder.blp.in"
	"builder.blp"
)

add_custom_command(
	OUTPUT 
	${GLADE_FILE}
	COMMAND	${blueprint_executable} compile --output ${GLADE_FILE} builder.blp
	VERBATIM
)

configure_file(
	"main.gresource.xml.in"
	"main.gresource.xml"
)

target_compile_definitions(${BIN_NAME} PRIVATE
	PROGRAM_RESOURCE_PATH="${PROGRAM_RESOURCE_PATH}"
	UI_RESOURCE_PATH="${ui_resource_path}"
)

if (WIN32)
	
	string(REPLACE "." "," PROGRAM_VERSION_COMMA ${PROGRAM_VERSION})
	set(platform_gresource "win.gresource.xml.in")
	configure_file("resource.rc.in" "resource.rc")
	target_sources(${BIN_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/resource.rc")

else()

	set(platform_gresource "unix.gresource.xml.in")

endif()

configure_file(
	${platform_gresource}
	${PLATFORM_GRESOURCE_XML}
)

configure_file(
	"desktop.in.in"
	"${PROJECT_NAME}.desktop.in"
)

add_custom_command(
	OUTPUT
	${MAIN_GRESOURCE_C}
	DEPENDS ${GLADE_FILE}
	COMMAND	${gcr_executable} --sourcedir=${CMAKE_CURRENT_BINARY_DIR} --target=${MAIN_GRESOURCE_C} --generate-source main.gresource.xml
	VERBATIM
)

add_custom_command(
	OUTPUT
	${PLATFORM_GRESOURCE_C}
	COMMAND	${gcr_executable} --sourcedir=${CMAKE_CURRENT_SOURCE_DIR} --target=${PLATFORM_GRESOURCE_C} --generate-source ${PLATFORM_GRESOURCE_XML}
	VERBATIM
)

add_custom_target(make-gresources DEPENDS ${MAIN_GRESOURCE_C} ${PLATFORM_GRESOURCE_C})

target_sources(${BIN_NAME} PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/${MAIN_GRESOURCE_C}" "${CMAKE_CURRENT_BINARY_DIR}/${PLATFORM_GRESOURCE_C}")

set(XGETTEXT_SOURCES ${XGETTEXT_SOURCES} ../data/${GLADE_FILE} ../data/${PROJECT_NAME}.desktop.in PARENT_SCOPE)