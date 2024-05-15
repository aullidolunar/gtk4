cmake_minimum_required (VERSION 3.20)

project (gtktest VERSION 1.0.0.1 LANGUAGES C)

find_package (PkgConfig REQUIRED)
pkg_check_modules (GTK4 REQUIRED gtk4)

add_executable(${PROJECT_NAME})
add_subdirectory(src)

target_compile_definitions (${PROJECT_NAME} PRIVATE PROJECT_ID="${PROJECT_NAME}" PROGRAM_NAME="${PROJECT_NAME} ${PROJECT_VERSION}")
target_include_directories (${PROJECT_NAME} PRIVATE ${GTK4_INCLUDE_DIRS})
target_link_directories (${PROJECT_NAME} PRIVATE ${GTK4_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${GTK4_LIBRARIES})

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)