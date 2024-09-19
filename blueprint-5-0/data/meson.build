# data

data_files_list = [
	'builder.blp.in', # 0
	'main.gresource.xml.in', # 1
	'unix.gresource.xml.in', # unix: 2
	'desktop.in', # unix: 3
	'resource.rc.in', # win: 2
	'win.gresource.xml.in' # win: 3
]

GNOME = import('gnome')

GRESOURCE_FILES_LIST = []

blueprint_executable = find_program('blueprint-compiler')

data_files = files(data_files_list[0], data_files_list[1])

blp_file = configure_file(
	input: data_files[0], # builder.blp.in
	output: 'builder.blp',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_TITLE': PROGRAM_TITLE
	}
)

builder_glade_file = 'builder.glade'
builder_file = custom_target(
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

I18N_SOURCES += builder_file.full_path()

UI_RESOURCE_PATH = PROGRAM_RES_PATH + '/' + builder_glade_file
PROGRAM_DEFS += [
	'-DUI_RESOURCE_PATH="' + UI_RESOURCE_PATH + '"',
]

GRESOURCE_FILES_LIST += configure_file(
	input: data_files[1], # main.gresource.xml.in
	output: 'main.gresource.xml',
	configuration: {
		'PROGRAM_NAME':	PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH,
		'GLADE_PATH': meson.current_build_dir(),
		'GLADE_FILE': builder_glade_file
	}
)

os_dir = IS_WIN ? 'win' : 'unix'

subdir(os_dir)

foreach gresource_file: GRESOURCE_FILES_LIST
	PROGRAM_SOURCES += GNOME.compile_resources(
		FS.name(gresource_file),
		gresource_file,
		dependencies: builder_file,
		source_dir: meson.current_source_dir() / os_dir
	)
endforeach
