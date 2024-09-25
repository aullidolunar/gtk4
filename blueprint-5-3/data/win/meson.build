# data/win

windows = import('windows')

new_desc = PROGRAM_DESC

resource = configure_file(
	input: 'resource.rc.in',
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_VERSION': PROGRAM_VERSION,
		'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
		'BIN_NAME': BIN_NAME, 
		'PROGRAM_DESCRIPTION': new_desc.format(gtk4_dep.version(), meson.version()) 
	}
)
	
PROGRAM_SOURCES += windows.compile_resources(
	resource,
	include_directories: meson.current_source_dir()
)

GRESOURCE_FILES_LIST += configure_file(
	input: 'win.gresource.xml.in',
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME
	}
)
