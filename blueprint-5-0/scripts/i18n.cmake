# scripts
	
find_program(GETTEXT_XGETTEXT_EXECUTABLE xgettext REQUIRED)
find_program(GETTEXT_MSGMERGE_EXECUTABLE msgmerge REQUIRED)
find_program(GETTEXT_MSGFMT_EXECUTABLE msgfmt REQUIRED)

function(I18N_PROGRAM_POT _program_name _potfile _sources_list)
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_SOURCE_DIR}/${_program_name}.pot
		DEPENDS
			${_sources_list}
		WORKING_DIRECTORY
			${PROJECT_SOURCE_DIR}
		COMMAND
			${GETTEXT_XGETTEXT_EXECUTABLE}
			--from-code=UTF-8
			--package-name=${_program_name}
			--package-version=${PROGRAM_VERSION}
			--msgid-bugs-address=aullidolunar@gmail.com
			--copyright-holder=aullidolunar
			--files-from=${CMAKE_CURRENT_SOURCE_DIR}/${_potfile}
			-c
			-k_
			-o
			${CMAKE_CURRENT_SOURCE_DIR}/${_program_name}.pot
		VERBATIM
	)
endfunction()

function(I18N_MAKE_LOCALES _program_bin _program_name _langs)
	add_custom_target(
		update-po
	)
	
	foreach(LANG ${_langs})
		add_custom_command(
			OUTPUT
				${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po
			DEPENDS
				${CMAKE_CURRENT_SOURCE_DIR}/${_program_name}.pot
			COMMAND
				${GETTEXT_MSGMERGE_EXECUTABLE}
				-U
				--backup=none
				${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po
				${CMAKE_CURRENT_SOURCE_DIR}/${_program_name}.pot
			VERBATIM
		)
		
		add_custom_command(
			OUTPUT
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES
			COMMAND
				${CMAKE_COMMAND}
				-E
				make_directory
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES
			VERBATIM
		)
		
		add_custom_command(
			OUTPUT
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES/${_program_name}.mo
			WORKING_DIRECTORY
				${CMAKE_CURRENT_SOURCE_DIR}
			COMMAND
				${GETTEXT_MSGFMT_EXECUTABLE}
				${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po
				-o
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES/${_program_name}.mo
			VERBATIM
		)
		
		add_custom_target(
			build-${LANG}-po
			DEPENDS
				${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po
			VERBATIM
		)
		add_custom_target(
			build-${LANG}-mo
			DEPENDS
				${CMAKE_CURRENT_SOURCE_DIR}/${LANG}.po
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES
				${CMAKE_CURRENT_BINARY_DIR}/${LANG}/LC_MESSAGES/${_program_name}.mo
			VERBATIM
		)
		add_dependencies(update-po build-${LANG}-po)
		add_dependencies(${_program_bin} build-${LANG}-mo)
	endforeach()
endfunction()

function(I18N_MAKE_DESKTOP_FILE _program_bin _program_name _desktop_template)
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop
		DEPENDS
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop.pre
		COMMAND
			Python3::Interpreter
			${PROJECT_SOURCE_DIR}/scripts/desktop_build_sys.py
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop.pre
			${BUILD_SYS}
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop
		VERBATIM
	)
	add_custom_command(
		OUTPUT
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop.pre
		COMMAND
			${GETTEXT_MSGFMT_EXECUTABLE}
			--desktop
			--template=${_desktop_template}
			-d
			${CMAKE_CURRENT_SOURCE_DIR}
			-o
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop.pre
		VERBATIM
	)
	add_custom_target(
		build-desktop-file
		DEPENDS
			${_desktop_template}
			${CMAKE_CURRENT_BINARY_DIR}/${_program_name}.desktop
		VERBATIM
	)
	add_dependencies(${_program_bin} build-desktop-file)
endfunction()