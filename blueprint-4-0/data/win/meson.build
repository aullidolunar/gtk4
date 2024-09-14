# data/win

win_data_files = files(data_files_list[4], data_files_list[5])

windows = import('windows')
	
resource = configure_file(
	input: win_data_files[0], # resource.rc.in
	output: 'resource.rc',
	configuration: {
		'PROGRAM_VERSION': PROGRAM_VERSION,
		'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
		'BIN_NAME': BIN_NAME, 
		'PROGRAM_DESCRIPTION': PROGRAM_DESC 
	}
)
	
PROGRAM_SOURCES += windows.compile_resources(
	resource,
	include_directories: meson.current_source_dir()
)

GRESOURCE_FILES_LIST += configure_file(
	input: win_data_files[1], # win.gresource.xml.in
	output: 'win.gresource.xml',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME
	}
)
