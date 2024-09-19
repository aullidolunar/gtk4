# data/unix

unix_data_files = files(data_files_list[2], data_files_list[3])

GRESOURCE_FILES_LIST += configure_file(
	input: unix_data_files[0], # unix.gresource.xml.in
	output: 'unix.gresource.xml',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH
	}
)

DESKTOP_IN = configure_file(
	input: unix_data_files[1], # desktop.in
	output: PROGRAM_NAME + '.desktop.in',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_DESC': PROGRAM_DESC,
		'PROGRAM_ICON': meson.current_source_dir() / 'linux-icon-64.png'
	}
)

I18N_SOURCES += DESKTOP_IN
