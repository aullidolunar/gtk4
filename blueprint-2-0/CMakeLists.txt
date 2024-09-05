# .

# mkdir build
# cd build
# cmake -G Ninja -DWITH_CAIRO=ON/OFF -DUSE_GTK_CSD=1/0 -DCMAKE_BUILD_TYPE=Debug/Release ..
# ninja
# ninja run
# ninja zip

# or

# cmake -S . -B build -G Ninja -DWITH_CAIRO=ON -DUSE_GTK_CSD=1 -DCMAKE_BUILD_TYPE=Debug
# cmake --build build --config Debug
# cmake --build build [-t run]

# i18n:

# to add/renove langs, first:
# cmake --build build -t remove-locales
# then, add/remove langs in LINGUAS, then:
# cmake --build build -t create-locales
# translate the po files as need it then build the locales:
# cmake --build build [-t run]

# to add/remove strings in sources, first renove old pot:
# cmake --build build -t remove-program-pot
# make changes in sources, then:
# cmake --build build -t update-locales
# translate the po files as need it then build the locales:
# cmake --build build [-t run]

cmake_minimum_required (VERSION 3.25)

project (blueprint VERSION 2.0.0.0 LANGUAGES C)

set(CMAKE_EXECUTABLE_ENABLE_EXPORTS TRUE)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK4_DEPS gtk4 gmodule-2.0 REQUIRED)

set (BIN_NAME "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}-${PROJECT_VERSION_MINOR}")
set (PROGRAM_NAME "${PROJECT_NAME}")
set (PROGRAM_VERSION "${PROJECT_VERSION}")
set (PROGRAM_TITLE "${PROJECT_NAME} ${PROJECT_VERSION}")
set (PROGRAM_DESC "Using Gtk ${GTK4_DEPS_gtk4_VERSION} and build with CMake ${CMAKE_VERSION}")
set (PROGRAM_ID "gtk4.aullidolunar.${PROJECT_NAME}")

add_executable(${BIN_NAME})
add_subdirectory(src)
add_subdirectory(data)
add_subdirectory(locale)

target_compile_definitions (${BIN_NAME} PRIVATE PROGRAM_NAME="${PROJECT_NAME}" PROGRAM_ID="${PROGRAM_ID}" PROGRAM_TITLE="${PROGRAM_TITLE}")
if (NOT DEFINED WITH_CAIRO OR WITH_CAIRO)
	target_compile_definitions(${BIN_NAME} PRIVATE "WITH_CAIRO")
endif()

if (NOT DEFINED USE_GTK_CSD OR USE_GTK_CSD)
	target_compile_definitions(${BIN_NAME} PRIVATE USE_GTK_CSD="${USE_GTK_CSD}")
endif()

message(STATUS "WITH_CAIRO=${WITH_CAIRO}")
message(STATUS "USE_GTK_CSD=${USE_GTK_CSD}")

target_include_directories (${BIN_NAME} PRIVATE ${GTK4_DEPS_INCLUDE_DIRS})
target_link_directories (${BIN_NAME} PRIVATE ${GTK4_DEPS_LIBRARY_DIRS})
target_link_libraries(${BIN_NAME} PRIVATE ${GTK4_DEPS_LIBRARIES})

add_custom_target(
	run
    COMMAND
		${BIN_NAME}
    DEPENDS
		${BIN_NAME}
)

find_program(7z_executable "7z")
if (7z_executable)
	cmake_path(GET CMAKE_CURRENT_BINARY_DIR FILENAME BUILD_DIRNAME)
	add_custom_target(zip
		COMMAND ${7z_executable} a -t7z "-xr!${BUILD_DIRNAME}" ${BIN_NAME}.7z ${PROJECT_SOURCE_DIR}
	)
endif()