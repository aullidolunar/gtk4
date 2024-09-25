# data/unix

GRESOURCE_FILES_LIST += configure_file(
	input: 'unix.gresource.xml.in',
	output: '@BASENAME@',
	configuration: {
		'PROGRAM_NAME': PROGRAM_NAME,
		'PROGRAM_RESOURCE_PATH': PROGRAM_RES_PATH
	}
)
