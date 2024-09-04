# data

blueprint_executable = find_program('blueprint-compiler')
gcr_executable = find_program('glib-compile-resources')

blp_file = 'builder.blp.in'
builder_glade_file = blp_file.replace('.blp.in', '.glade')
blueprint_file = configure_file(
	input: blp_file,
	output: blp_file.substring(0, -3),
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_TITLE': PROGRAM_TITLE
	}
)

builder_glade = custom_target(
	'builder-glade-compiler',
	input: blueprint_file,
	output: builder_glade_file,
	command: [
		blueprint_executable,
		'compile',
		'--output',
		'@OUTPUT@',
		'@INPUT@'
	]
)

program_resource_path = '/' + PROGRAM_ID.replace('.', '/')
ui_resource_path = program_resource_path + '/' + builder_glade_file

PROGRAM_DEFS += [
	'-DPROGRAM_RESOURCE_PATH="' + program_resource_path + '"',
	'-DUI_RESOURCE_PATH="' + ui_resource_path + '"',
]

I18N_SOURCES += builder_glade

builder_glade_dir = FS.parent(builder_glade)

gresource_data = configuration_data()
gresource_data.set('PROGRAM_NAME', PROGRAM_NAME)
gresource_data.set('PROGRAM_RESOURCE_PATH', program_resource_path)
gresource_data.set('GLADE_FILE', builder_glade_file)
gresource_data.set('PROJECT_DATA_DIR', meson.current_source_dir())

main_gresource_xml = configure_file(
	input: 'main.gresource.xml.in',
	output: 'main.gresource.xml',
	configuration: gresource_data
)

if IS_WIN
	
	windows = import('windows')
	platform_gresource = files('win.gresource.xml.in')
	
	resource_in = files('resource.rc.in')
	resource = configure_file(
		input: resource_in,
		output: 'resource.rc',
		configuration: { 
			'PROGRAM_VERSION': PROGRAM_VERSION,
			'PROGRAM_VERSION_COMMA': PROGRAM_VERSION.replace('.', ','),
			'BIN_NAME': BIN_NAME, 
			'PROGRAM_DESCRIPTION': PROGRAM_DESC 
		}
	)
	
	PROGRAM_SOURCES +=  windows.compile_resources(
		resource,
		include_directories: meson.current_source_dir()
	)
	
else
	
	platform_gresource = files('unix.gresource.xml.in')
	
endif

PROGRAM_SOURCES += custom_target(
	'main_gresource_c',
	output: 'main.gresource.c',
	input: main_gresource_xml,
	depends: builder_glade,
	command: [
		gcr_executable,
		'--sourcedir=' + builder_glade_dir,
		'--target=@OUTPUT@',
		'--generate-source',
		'@INPUT@'
	]
)

platform_gresource_xml = configure_file(
	input: platform_gresource,
	output: 'platform.gresource.xml',
	configuration: gresource_data
)

PROGRAM_SOURCES += custom_target(
	'platform-gresource-c',
	output: 'platform.gresource.c',
	input: platform_gresource_xml,
	command: [
		gcr_executable,
		'--sourcedir=' + meson.current_source_dir(),
		'--target=@OUTPUT@',
		'--generate-source',
		'@INPUT@'
	]
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

I18N_SOURCES += DESKTOP_IN