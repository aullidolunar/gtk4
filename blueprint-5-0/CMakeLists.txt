# .

# Warning!!!
# if you are testing with cmake and meson build systems, even OSs, POTFILES may have different sources paths.
# To keep cmake happy:
# cmake -B cmake_build -G Ninja -DWITH_CAIRO=ON -DUSE_GTK_CSD=1 -DENABLE_MAINTAINER=TRUE
# see if POTFILES has meson build paths, then:
# cmake -B cmake_build -G Ninja -DWITH_CAIRO=ON -DUSE_GTK_CSD=1 -DENABLE_MAINTAINER=FALSE
# 

# ninja -C cmake_build [run]
# or
# samu -C cmake_build [run]

# i18n:
# edit LINGUAS or add source files with _() for translation as need it. Then:
# cmake -B cmake_build -G Ninja -DWITH_CAIRO=ON -DUSE_GTK_CSD=1 -DENABLE_MAINTAINER=TRUE
# see if LINGUAS and POTFILES are written correctly. Then:
# cmake -B cmake_build -G Ninja -DWITH_CAIRO=ON -DUSE_GTK_CSD=1 -DENABLE_MAINTAINER=FALSE
# samu -C cmake_build update-po
# Edit po files as need it. Then:
# meson compile -C build [run]

cmake_minimum_required(VERSION 3.20)
project(blueprint VERSION 5.0.0.1 LANGUAGES C)

set(BUILD_SYS "CMake ${CMAKE_VERSION}")

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK4 REQUIRED gtk4 gmodule-2.0)

find_package(Python3 REQUIRED)

if(NOT DEFINED USE_GTK_CSD)
	set(USE_GTK_CSD "1")
endif()

if (NOT DEFINED WITH_CAIRO)
	set(WITH_CAIRO ON)
endif()

if (NOT DEFINED ENABLE_MAINTAINER)
	set(ENABLE_MAINTAINER FALSE)
endif()

message(STATUS "WITH_CAIRO: ${WITH_CAIRO}")
message(STATUS "USE_GTK_CSD: ${USE_GTK_CSD}")
message(STATUS "ENABLE_MAINTAINER: ${ENABLE_MAINTAINER}")

set(CMAKE_ENABLE_EXPORTS ON)

set(PROGRAM_NAME "${PROJECT_NAME}")
set(PROGRAM_VERSION "${PROJECT_VERSION}")
set(PROGRAM_TITLE "${PROJECT_NAME} ${PROJECT_VERSION}")
set(PROGRAM_DESC "Compile using Gtk ${GTK4_gtk4_VERSION} and build with %s")
set(BIN_NAME "${PROGRAM_NAME}-${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")
set(PROGRAM_ID "gtk4.aullidolunar.${PROGRAM_NAME}")
string(REPLACE "." "/" PROGRAM_RESOURCE_PATH ${PROGRAM_ID})
string(PREPEND PROGRAM_RESOURCE_PATH "/")

add_executable (${BIN_NAME})

target_compile_definitions(
	${BIN_NAME} PRIVATE
	PROGRAM_NAME="${PROGRAM_NAME}"
	PROGRAM_TITLE="${PROGRAM_TITLE}"
	PROGRAM_ID="${PROGRAM_ID}"
	PROGRAM_RESOURCE_PATH="${PROGRAM_RESOURCE_PATH}"
	USE_GTK_CSD="${USE_GTK_CSD}"
	WITH_CAIRO
)

target_include_directories(${BIN_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_directories(${BIN_NAME} PRIVATE ${GTK4_LIBRARY_DIRS})
target_link_libraries(${BIN_NAME} PRIVATE ${GTK4_LIBRARIES})

set(I18N_SOURCES "")
add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(locale)

add_custom_target(
	run
    COMMAND
		${BIN_NAME}
    VERBATIM
)

find_program(ZIP_EXECUTABLE "7z")

if (ZIP_EXECUTABLE)

	cmake_path(GET PROJECT_SOURCE_DIR PARENT_PATH rootName)
	cmake_path(GET PROJECT_SOURCE_DIR FILENAME channel)

	add_custom_target(
		zip
		WORKING_DIRECTORY
			${rootName}
		COMMAND
			${ZIP_EXECUTABLE}
			a
			-t7z
			-xr!*_build
			${CMAKE_CURRENT_BINARY_DIR}/${channel}.7z
			${channel}
		VERBATIM
	)

endif()
