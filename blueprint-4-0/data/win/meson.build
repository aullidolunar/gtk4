# data/win

PROGRAM_DATA_FILES += files(data_files[4], data_files[5])

windows = import('windows')
	
resource = configure_file(
	input: PROGRAM_DATA_FILES[2], # resource.rc.in
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

win_gresource_xml = configure_file(
	input: PROGRAM_DATA_FILES[3], # win.gresource.xml.in
	output: 'win.gresource.xml',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME
	}
)

PROGRAM_SOURCES += GNOME.compile_resources(
	'win.gresource.xml',
	win_gresource_xml,
	source_dir: meson.current_source_dir()
)
