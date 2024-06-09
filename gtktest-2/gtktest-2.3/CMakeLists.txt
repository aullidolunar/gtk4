
cmake_minimum_required (VERSION 3.20)

project (gtktest VERSION 2.3.0.1 LANGUAGES C)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK4 REQUIRED gtk4)

set (BIN_NAME "${PROJECT_NAME}-${PROJECT_VERSION}")

add_executable (${BIN_NAME})
add_subdirectory (data)
add_subdirectory (src)

target_compile_definitions (${BIN_NAME} PRIVATE
	PROGRAM_NAME="${PROJECT_NAME}"
	PROJECT_NAME_TITLE="${PROJECT_NAME} ${PROJECT_VERSION}"
	PROJECT_APPID="gtk4.aullidolunar.${PROJECT_NAME}"
)
target_include_directories (${BIN_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_directories (${BIN_NAME} PRIVATE ${GTK4_LIBRARY_DIRS})
target_link_libraries (${BIN_NAME} PRIVATE ${GTK4_LIBRARIES})

add_custom_target(run
    COMMAND ${BIN_NAME}
    DEPENDS ${BIN_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)
