# data/win

windows = import('windows')

new_desc = PROGRAM_DESC

resource = configure_file(
	input: files('resource.rc.in'),
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_VERSION': PROGRAM_VERSION,
		'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
		'BIN_NAME': BIN_NAME, 
		'PROGRAM_DESCRIPTION': new_desc.format(TOOLKIT_VERSION, MESON_VERSION) 
	}
)
	
PROGRAM_SOURCES += windows.compile_resources(
	resource,
	include_directories: meson.current_source_dir()
)

win_gresource_xml = configure_file(
	input: files('win.gresource.xml.in'),
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH
	}
)

PROGRAM_SOURCES += custom_target(
  input: win_gresource_xml,
  output: '@PLAINNAME@.c',
  command: [
	glib_compile_resources_executable,
	'--target=@OUTPUT@',
	'--sourcedir=' + meson.current_source_dir(),
	'--generate-source',
	'@INPUT@'
  ]
)
