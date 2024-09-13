# data/unix

PROGRAM_DATA_FILES += files(data_files[2], data_files[3])

unix_gresource_xml = configure_file(
	input: PROGRAM_DATA_FILES[2], # unix.gresource.xml.in
	output: 'unix.gresource.xml',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH
	}
)

PROGRAM_SOURCES += GNOME.compile_resources(
	'unix.gresource.xml.c',
	unix_gresource_xml,
	source_dir: meson.current_source_dir()
)

DESKTOP_IN = configure_file(
	input: PROGRAM_DATA_FILES[3], # desktop.in
	output: PROGRAM_NAME + '.desktop.in',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_DESC': PROGRAM_DESC,
		'PROGRAM_ICON': meson.current_source_dir() / 'linux-icon-64.png'
	}
)

I18N_SOURCES += DESKTOP_IN