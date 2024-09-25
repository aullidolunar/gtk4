# data

GNOME = import('gnome')

blueprint_executable = find_program('blueprint-compiler', required: true)

blp_file = configure_file(
	input: 'builder.glade.blp.in',
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_TITLE': PROGRAM_TITLE
	}
)

builder_file = custom_target(
	input: blp_file,
	output: '@BASENAME@',
	command: [
		blueprint_executable,
		'compile',
		'--output',
		'@OUTPUT@',
		'@INPUT@'
	]

)

builder_glade_file = FS.name(builder_file)

UI_RESOURCE_PATH = PROGRAM_RES_PATH + '/' + builder_glade_file
PROGRAM_DEFS += [
	'-DUI_RESOURCE_PATH="' + UI_RESOURCE_PATH + '"',
]

GRESOURCE_FILES_LIST = []

GRESOURCE_FILES_LIST += configure_file(
	input: 'main.gresource.xml.in',
	output: '@BASENAME@',
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

DESKTOP_FILE_IN = configure_file(
	input: 'desktop.in.in',
	output: PROGRAM_NAME + '.template.@BASENAME@',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_DESC': PROGRAM_DESC,
		'PROGRAM_ICON': meson.current_source_dir() / 'tux-logo-24.png'
	}
)

I18N_SOURCES += [
	FS.relative_to(builder_file, meson.project_source_root()),
	FS.relative_to(DESKTOP_FILE_IN, meson.project_source_root())
]
