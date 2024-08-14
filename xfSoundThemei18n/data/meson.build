# data

conf_data = configuration_data()
conf_data.set('PROGRAM_NAME', meson.project_name())
conf_data.set('PROGRAM_ICON', meson.project_name() + '.png')
conf_data.set('PROGRAM_DESC', PROGRAM_DESC)

xgettext_path = find_program('xgettext')

pot_files = []

pot_files += custom_target(
	'create-sources-pot',
	output: 'sources.pot',
	command :  [
		xgettext_path,
		'--from-code=UTF-8',
		'--package-name=' + meson.project_name() + '',
		'--package-version=' + meson.project_version() + '',
		'--msgid-bugs-address=aullidolunar@gmail.com',
		'--copyright-holder=aullidolunar',
		'-k',
		'-k_',
		'--language=C',
		'-c',
		'-o',
		'@OUTPUT@',
		SOURCES_I18N
	]
)

if fs.is_file('desktop.in')

	desktop_in = configure_file(
		input : 'desktop.in',
		output : meson.project_name() + '.desktop.in',
		configuration : conf_data
	)

	pot_files += custom_target(
		'create-desktop-pot',
		input: desktop_in,
		output: 'desktop.pot',
		command :  [
			xgettext_path,
			'--from-code=UTF-8',
			'--package-name=' + meson.project_name() + '',
			'--package-version=' + meson.project_version() + '',
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
endif

pot_file = custom_target(
	'create-pot',
	input: pot_files,
	output: meson.project_name() + '.pot',
	depends: pot_files,
	command :  [
		xgettext_path,
		'--from-code=UTF-8',
		'--package-name=' + meson.project_name() + '',
		'--package-version=' + meson.project_version() + '',
		'--msgid-bugs-address=aullidolunar@gmail.com',
		'--copyright-holder=aullidolunar',
		'-c',
		'-o',
		'../@OUTPUT@',
		'@INPUT@'
	]
)
gcr_path = find_program('glib-compile-resources')

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
	rc_data.set('BIN_NAME', BIN_NAME)

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
