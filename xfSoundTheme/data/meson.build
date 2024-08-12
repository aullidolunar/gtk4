# data

gcr_path = find_program('glib-compile-resources')

conf_data = configuration_data()
conf_data.set('PROGRAM_NAME', meson.project_name())

gresource_xml = configure_file(
	input : 'resource.gresource.xml.in',
	output : 'resource.gresource.xml',
	configuration : conf_data
)

gresource_c = custom_target('gresource_c',
	output : 'gresource.c',
	input : gresource_xml,
	command : [
		gcr_path,
		'--sourcedir=../data/',
		'--target=@OUTPUT@',
		'--generate-source',
		'@INPUT@'
	]
)

PROGRAM_SOURCES += gresource_c

if build_machine.system() == 'windows'

	windres_path = find_program('windres')

	rc_data = configuration_data()
	rc_data.set('PROGRAM_NAME', meson.project_name())
	rc_data.set('PROGRAM_VERSION', meson.project_version())
	rc_data.set('PROGRAM_VERSION_COMMA', meson.project_version().replace('.', ','))
	rc_data.set('PROGRAM_DESCRIPTION', PROGRAM_DESC)
	rc_data.set('DATA_DIR',  meson.current_source_dir())
	rc_data.set('BIN_NAME', bin_name)
	
	resource_rc = configure_file(
		input : 'resource.rc.in',
		output : 'resource.rc',
		configuration : rc_data
	)
	
	resource_res = custom_target('resource_res',
		output : 'resource.res',
		input : resource_rc,
		command : [
			windres_path,
			'-i',
			'@INPUT@',
			'-O',
			'coff',
			'-o',
			'@OUTPUT@'
		]
	)

	PROGRAM_SOURCES += resource_res
	
	win_gresource_c = custom_target('win_gresource_c',
		output : 'win_gresource.c',
		input : 'windows.resource.gresource.xml',
		command : [
			gcr_path,
			'--sourcedir=../data/',
			'--target=@OUTPUT@',
			'--generate-source',
			'@INPUT@'
		]
	)

	PROGRAM_SOURCES += win_gresource_c

else
	
	linux_gresource_xml = configure_file(
		input : 'linux.resource.gresource.xml.in',
		output : 'linux.resource.gresource.xml',
		configuration : conf_data
	)

	linux_gresource_c = custom_target('linux_gresource_c',
		output : 'linux_gresource.c',
		input : linux_gresource_xml,
		command : [
			gcr_path,
			'--sourcedir=../data/',
			'--target=@OUTPUT@',
			'--generate-source',
			'@INPUT@'
		]
	)

	PROGRAM_SOURCES += linux_gresource_c
	
endif
