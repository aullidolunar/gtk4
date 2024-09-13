# data

data_files = [
	'builder.blp.in', # 0
	'main.gresource.xml.in', # 1
	'unix.gresource.xml.in', # unix: 2
	'desktop.in', # unix: 3
	'resource.rc.in', # win: 2
	'win.gresource.xml.in' # win: 3
]

GNOME = import('gnome')

blueprint_executable = find_program('blueprint-compiler')

PROGRAM_DATA_FILES = files(data_files[0], data_files[1])

blp_file = configure_file(
	input: PROGRAM_DATA_FILES[0], # builder.blp.in
	output: 'builder.blp',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_TITLE': PROGRAM_TITLE
	}
)

builder_glade_file = 'builder.glade'
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

UI_RESOURCE_PATH = PROGRAM_RES_PATH + '/' + builder_glade_file
PROGRAM_DEFS += [
	'-DUI_RESOURCE_PATH="' + UI_RESOURCE_PATH + '"',
]

main_gresource_xml = configure_file(
	input: PROGRAM_DATA_FILES[1], # main.gresource.xml.in
	output: 'main.gresource.xml',
	configuration: {
		'PROGRAM_NAME':	PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH,
		'GLADE_PATH': meson.current_build_dir(),
		'GLADE_FILE': builder_glade_file
	}
)

PROGRAM_SOURCES += GNOME.compile_resources(
	'main.gresource.xml',
	main_gresource_xml,
	source_dir: meson.current_source_dir(),
	dependencies: builder_glade
)

if IS_WIN	
	subdir('win')
else
	subdir('unix')
endif

I18N_SOURCES += builder_glade
