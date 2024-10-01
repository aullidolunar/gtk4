# data

glib_compile_resources_executable = find_program('glib-compile-resources', required: true)

blueprint_executable = find_program('blueprint-compiler', required: true)

builder_file = custom_target(
  input: files('builder.glade.blp'),
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

main_gresource_xml = configure_file(
  input: files('main.gresource.xml.in'),
  output: '@BASENAME@',
  configuration: {
    'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH,
    'GLADE_FILE': builder_glade_file
  }
)

PROGRAM_SOURCES += custom_target(
  input: [main_gresource_xml, builder_file],
  output: '@PLAINNAME0@.c',
  command: [
	glib_compile_resources_executable,
	'--target=@OUTPUT@',
	'--sourcedir=' + meson.current_source_dir(),
	'--sourcedir=' + meson.current_build_dir(),
	'--generate-source',
	'@INPUT0@'
  ]
)

subdir(IS_WIN ? 'win' : 'unix')

DESKTOP_FILE_IN = configure_file(
  input: files('desktop.in.in'),
  output: 'template.@BASENAME@',
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
