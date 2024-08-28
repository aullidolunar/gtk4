# data

desktop_file = files('desktop.in')
XGETTEXT_EXECUTABLE = find_program('xgettext')
gcr_executable = find_program('glib-compile-resources')

conf_data = configuration_data()
conf_data.set('PROGRAM_NAME', PROGRAM_NAME)
conf_data.set('PROGRAM_ICON', PROGRAM_NAME + '.png')
conf_data.set('PROGRAM_DESC', PROGRAM_DESC)

POT_FILE = meson.current_source_dir() /  PROGRAM_NAME + '.pot'
POT_FILES = []

POT_FILES += custom_target(
	'create-sources-pot',
	output: 'sources.pot',
	command:  [
		XGETTEXT_EXECUTABLE,
		'--from-code=UTF-8',
		'--package-name=' + PROGRAM_NAME + '',
		'--package-version=' + PROGRAM_VERSION + '',
		'--msgid-bugs-address=aullidolunar@gmail.com',
		'--copyright-holder=aullidolunar',
		'-k',
		'-k_',
		'--language=C',
		'-c',
		'-o',
		'@OUTPUT@',
		I18N_SOURCES
	]
)

DESKTOP_IN = configure_file(
	input: desktop_file,
	output: PROGRAM_NAME + '.desktop.in',
	configuration: conf_data
)

POT_FILES += custom_target(
	'create-desktop-pot',
	input: DESKTOP_IN,
	output: 'desktop.pot',
	command:  [
		XGETTEXT_EXECUTABLE,
		'--from-code=UTF-8',
		'--package-name=' + PROGRAM_NAME + '',
		'--package-version=' + PROGRAM_VERSION + '',
		'--msgid-bugs-address=aullidolunar@gmail.com',
		'--copyright-holder=aullidolunar',
		'-k',
		'-kComment',
		'--language=Desktop',
		'-c',
		'-o',
		'@OUTPUT@',
		'@INPUT@'
	]
)

gresource_xml = configure_file(
	input: 'resource.gresource.xml.in',
	output: 'resource.gresource.xml',
	configuration: conf_data
)

PROGRAM_SOURCES += custom_target(
	'gresource_c',
	output: 'gresource.c',
	input: gresource_xml,
	command : [
		gcr_executable,
		'--sourcedir=../data/',
		'--target=@OUTPUT@',
		'--generate-source',
		'@INPUT@'
	]
)

if build_machine.system() == 'windows'

	windows = import('windows')

	rc_data = configuration_data()
	rc_data.set('PROGRAM_NAME', PROGRAM_NAME)
	rc_data.set('PROGRAM_VERSION', PROGRAM_VERSION)
	rc_data.set('PROGRAM_VERSION_COMMA', PROGRAM_VERSION.replace('.', ','))
	rc_data.set('PROGRAM_DESCRIPTION', PROGRAM_DESC)
	rc_data.set('DATA_DIR', meson.current_source_dir())
	rc_data.set('BIN_NAME', BIN_NAME)

	resource_rc = configure_file(
		input: 'resource.rc.in',
		output: 'resource.rc',
		configuration: rc_data
	)

	PROGRAM_SOURCES += windows.compile_resources(
		resource_rc
	)

	PROGRAM_SOURCES += custom_target('win_gresource_c',
		output: 'win_gresource.c',
		input: 'windows.resource.gresource.xml',
		command: [
			gcr_executable,
			'--sourcedir=../data/',
			'--target=@OUTPUT@',
			'--generate-source',
			'@INPUT@'
		]
	)

else

	linux_gresource_xml = configure_file(
		input: 'linux.resource.gresource.xml.in',
		output: 'linux.resource.gresource.xml',
		configuration: conf_data
	)

	PROGRAM_SOURCES += custom_target(
		'linux_gresource_c',
		output: 'linux_gresource.c',
		input: linux_gresource_xml,
		command: [
			gcr_executable,
			'--sourcedir=../data/',
			'--target=@OUTPUT@',
			'--generate-source',
			'@INPUT@'
		]
	)

endif

'''
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
'''