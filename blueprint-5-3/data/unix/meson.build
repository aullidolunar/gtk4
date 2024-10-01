# data/unix

unix_gresource_xml = configure_file(
  input: files('unix.gresource.xml.in'),
  output: '@BASENAME@',
  configuration: {
    'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH,
    'PROGRAM_NAME': PROGRAM_NAME
  }
)

PROGRAM_SOURCES += custom_target(
  input: unix_gresource_xml,
  output: '@PLAINNAME@.c',
  command: [
	glib_compile_resources_executable,
	'--target=@OUTPUT@',
	'--sourcedir=' + meson.current_source_dir(),
	'--generate-source',
	'@INPUT@'
  ]
)
