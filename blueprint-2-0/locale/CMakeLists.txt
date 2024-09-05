# locale

find_program(xgettext_executable "xgettext" REQUIRED)
find_program(msginit_executable "msginit" REQUIRED)
find_program(msgfmt_executable "msgfmt" REQUIRED)
find_program(msgmerge_executable "msgmerge" REQUIRED)

set(PROGRAM_POT "${PROGRAM_NAME}.pot")

file(READ "LINGUAS" linguas)
string(REPLACE "\n" ";" langs ${linguas})

add_custom_command(
	OUTPUT 
		${PROGRAM_POT}
	COMMAND
		${xgettext_executable}
		--from-code=UTF-8
		--package-name=${PROGRAM_NAME}
		--package-version=${PROGRAM_VERSION}
		--msgid-bugs-address=aullidolunar@gmail.com
		--copyright-holder=aullidolunar
		-k_
		-kN_
		-o
		${PROGRAM_POT}
		${XGETTEXT_SOURCES}
	VERBATIM
)

add_custom_target(
	remove-program-pot
	COMMAND
		${CMAKE_COMMAND}
		-E
		remove
		../${PROGRAM_POT}
	VERBATIM
)

add_custom_target(create-locales DEPENDS ${PROGRAM_POT} VERBATIM)
add_custom_target(update-locales DEPENDS ${PROGRAM_POT} VERBATIM)
add_custom_target(build-locales VERBATIM)
add_custom_target(remove-locales VERBATIM)

foreach(lang ${langs})

set(po_path "../../locale/${lang}.po")
set(mo_path "${lang}/LC_MESSAGES")

add_custom_command(
	OUTPUT
		${po_path}
	COMMAND
		${msginit_executable}
		-l
		${lang}.UTF-8
		--no-translator
		-o
		${po_path}
		-i
		${PROGRAM_POT}
	VERBATIM
)

add_custom_target(
	update-${lang}-po
	COMMAND
		${msgmerge_executable}
		-U
		--backup=off
		${po_path}
		${PROGRAM_POT}
	VERBATIM
)

add_custom_command(
	OUTPUT 
		${mo_path}
	COMMAND
		${CMAKE_COMMAND}
		-E
		make_directory
		${directory}
		${mo_path}
	VERBATIM
)
	
add_custom_command(
	OUTPUT 
		${mo_path}/${PROGRAM_NAME}.mo
	COMMAND
		${msgfmt_executable}
		-o
		${mo_path}/${PROGRAM_NAME}.mo
		${po_path}
	VERBATIM
)

add_custom_target(
	remove-${lang}-po
	COMMAND
		${CMAKE_COMMAND}
		-E
		remove
		../../locale/${lang}.po
	VERBATIM
)

add_custom_target(
	remove-${lang}-mo
	COMMAND
		${CMAKE_COMMAND}
		-E
		remove
		${mo_path}/${PROGRAM_NAME}.mo
	VERBATIM
)

add_custom_target(create-${lang}-po DEPENDS ${po_path} VERBATIM)
add_dependencies(create-locales create-${lang}-po)

add_dependencies(update-locales update-${lang}-po)

add_custom_target(create-${lang}-mo DEPENDS ${mo_path}/${PROGRAM_NAME}.mo VERBATIM)
add_dependencies(build-locales create-${lang}-mo)
add_dependencies(${BIN_NAME} build-locales)

add_dependencies(remove-locales remove-${lang}-po)

add_dependencies(remove-program-pot remove-${lang}-mo)

endforeach()

if (EXISTS "${PROJECT_BINARY_DIR}/data/${PROGRAM_NAME}.desktop.in")

add_custom_command(
	OUTPUT 
		${PROGRAM_NAME}.desktop
	WORKING_DIRECTORY
		${PROJECT_BINARY_DIR}
	COMMAND
		${msgfmt_executable}
		--desktop
		--template=data/${PROGRAM_NAME}.desktop.in
		-d
		../locale
		-o
		${PROGRAM_NAME}.desktop
	VERBATIM
)

add_custom_target(
	desktop-file
	DEPENDS
		${PROGRAM_NAME}.desktop
)

add_dependencies(${BIN_NAME} desktop-file)

endif()
