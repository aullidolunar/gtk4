# data/unix

GRESOURCE_FILES_LIST += configure_file(
	input: 'unix.gresource.xml.in',
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH
	}
)

DESKTOP_IN = configure_file(
	input: 'desktop.in',
	output: PROGRAM_NAME + '.desktop.in',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_DESC': PROGRAM_DESC,
		'PROGRAM_ICON': meson.current_source_dir() / 'linux-icon-64.png'
	}
)

I18N_SOURCES += FS.relative_to(DESKTOP_IN, meson.project_source_root())
