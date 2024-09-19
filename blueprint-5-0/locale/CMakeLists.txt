# locale

set(POTFILES_FILE "POTFILES")

file(READ "LINGUAS" LINGUAS)
string(STRIP ${LINGUAS} LINGUAS_STRIPED)
string(REPLACE " " ";" LANGS ${LINGUAS_STRIPED})
	
if (ENABLE_MAINTAINER)

	foreach(LANG ${LANGS})
		if(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po)
			message(STATUS "${LANG}.po: not found and was created.")
			file(TOUCH ${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po)
		else()
			message(STATUS "${LANG}.po: exists and no need to be created.")
		endif()
	endforeach()
	
	if (EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${POTFILES_FILE}")
		file(WRITE "${CMAKE_CURRENT_SOURCE_DIR}/${POTFILES_FILE}" "")
	endif()
	foreach(loc ${I18N_SOURCES})
		cmake_path(RELATIVE_PATH loc BASE_DIRECTORY "${PROJECT_SOURCE_DIR}" OUTPUT_VARIABLE _src)
		file(APPEND "${CMAKE_CURRENT_SOURCE_DIR}/${POTFILES_FILE}" "${_src}\n")
	endforeach()

else()

	include(../scripts/i18n.cmake)
	
	I18N_PROGRAM_POT("${PROGRAM_NAME}" "${POTFILES_FILE}" ${I18N_SOURCES})
	# generate update-po target and compile po to mo file on build time:
	I18N_MAKE_LOCALES("${BIN_NAME}" "${PROGRAM_NAME}" "${LANGS}")
	
	if (NOT WIN32)
		# generate desktop file on build time:
		I18N_MAKE_DESKTOP_FILE(
			"${BIN_NAME}"
			"${PROGRAM_NAME}"
			"${PROJECT_BINARY_DIR}/data/unix/${PROGRAM_NAME}.desktop.in"
		)
	endif()

# https://p-o.co.uk/tech-articles/using-cmake-to-update-gettext-pot-po-and-mo-files/

endif()