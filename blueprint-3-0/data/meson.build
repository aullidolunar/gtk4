# data

data_files = [
	'builder.blp.in',
	'main.gresource.xml.in',
	'desktop.in',
	'unix.gresource.xml.in',
	'win.gresource.xml.in',
	'resource.rc.in'
]

data_sources = files([data_files])

gresource_files = []

blueprint_executable = find_program('blueprint-compiler')
gcr_executable = find_program('glib-compile-resources')

blp_file = configure_file(
	input: data_sources.get(0), # builder.blp.in
	output: data_files.get(0).substring(0, -3), # builder.blp
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_TITLE': PROGRAM_TITLE
	}
)

builder_glade_file = data_files.get(0).replace('.blp.in', '.glade')
builder_glade = custom_target(
	input: blp_file,
	output: builder_glade_file,
	command: [
		blueprint_executable,
		'compile',
		'--output',
		'@OUTPUT@',
		'@INPUT@'
	]
)

UI_RESOURCE_PATH = PROGRAM_RESOURCE_PATH + '/' + builder_glade_file
PROGRAM_DEFS += [
	
	'-DUI_RESOURCE_PATH="' + UI_RESOURCE_PATH + '"',
]

builder_glade_dir = FS.parent(builder_glade)

gresource_data = configuration_data()
gresource_data.set('PROGRAM_NAME', PROGRAM_NAME)
gresource_data.set('PROGRAM_RESOURCE_PATH', PROGRAM_RESOURCE_PATH)
gresource_data.set('GLADE_FILE', builder_glade_file)
gresource_data.set('PROJECT_DATA_DIR', meson.current_build_dir())

gresource_files += configure_file(
	input: data_sources.get(1), # main.gresource.xml.in
	output: data_files.get(1).substring(0, -3), # main.gresource.xml
	configuration: gresource_data
)

if IS_WIN
		
	windows = import('windows')
	
	resource = configure_file(
		input: data_sources.get(5), # resource.rc.in
		output: data_files.get(5).substring(0, -3), # resource.rc
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
	
	platform_gresource = data_files.get(4) # win.gresource.xml.in
	
else

	platform_gresource = data_files.get(3) # unix.gresource.xml.in

endif

gresource_files += configure_file(
	input: platform_gresource,
	output: FS.replace_suffix(platform_gresource, ''), # platform.gresource.xml
	configuration: gresource_data
)

foreach gres: gresource_files

PROGRAM_SOURCES += custom_target(
	input: gres,
	output: FS.stem(gres) + '.c', 
	depends: builder_glade,
	command: [
		gcr_executable,
		'--sourcedir=' + meson.current_source_dir(),
		'--target=@OUTPUT@',
		'--generate-source',
		'@INPUT@'
	]
)

endforeach

DESKTOP_IN = configure_file(
	input: data_sources.get(2), # desktop.in
	output: PROGRAM_NAME + '.desktop.in',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_DESC': PROGRAM_DESC,
		'PROGRAM_ICON': meson.current_source_dir() / 'linux-icon-64.png'
	}
)

if ENABLE_I18L
	I18N_SOURCES += [builder_glade, DESKTOP_IN]
endif
