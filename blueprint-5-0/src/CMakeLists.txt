# src

set(PROGRAM_SOURCES callbacks.c main.c)

foreach(src ${PROGRAM_SOURCES})
	list(APPEND I18N_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/${src}")
endforeach()

set(I18N_SOURCES ${I18N_SOURCES} PARENT_SCOPE)

target_sources(${BIN_NAME} PRIVATE ${PROGRAM_SOURCES})
