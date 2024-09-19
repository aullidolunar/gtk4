# locale

if not get_option('ENABLE_MAINTAINER')

# https://mesonbuild.com/i18n-module.html#i18n-module
# https://mesonbuild.com/Localisation.html#localisation
	
	i18n = import('i18n')
	
	gettext = i18n.gettext(
		meson.project_name(),
		args: [
			'--from-code=UTF-8',
			'--msgid-bugs-address="aullidolunar@gmail.com"',
			'--package-version="' + PROGRAM_VERSION + '"'
		]
	)
	
	# build mo files:
	I18N_DEPS += gettext[0]

	if not IS_WIN
		
		desktop_file = i18n.merge_file(
			input: DESKTOP_IN,
			output: PROGRAM_NAME + '.desktop.pre',
			type: 'desktop',
			po_dir: meson.current_source_dir()
		)
		
		I18N_DEPS += custom_target(
			input: desktop_file,
			output: PROGRAM_NAME + '.desktop',
			depends: desktop_file,
			command: [
				PYTHON_EXECUTABLE,
				DESKTOP_BUILD_SYS,
				'@INPUT@',
				BUILD_SYS,
				'@OUTPUT@'
			]
		)
	
	endif
	
else
	
	run_command(
		PYTHON_EXECUTABLE,
		GENPOT,
		meson.current_source_dir(),
		I18N_SOURCES,
		check: false
	)

endif