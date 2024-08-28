# locales

linguas = files('LINGUAS')
locale_dep = []

msginit_executable = find_program('msginit')
msgfmt_executable = find_program('msgfmt')
msgmerge_executable = find_program('msgmerge')

langs = FS.read(linguas).strip().split('\n')

run_target(
	'create-pot',
	depends: POT_FILES,
	command: [
		XGETTEXT_EXECUTABLE,
		'--from-code=UTF-8',
		'--package-name=' + PROGRAM_NAME + '',
		'--package-version=' + PROGRAM_VERSION + '',
		'--msgid-bugs-address=aullidolunar@gmail.com',
		'--copyright-holder=aullidolunar',
		'-c',
		'-o',
		POT_FILE,
		POT_FILES
	]
)

linguas_po = custom_target(
	'create-po',
	output: 'LINGUAS',
	depends: POT_FILES,
	command: [
		PYTHON_EXECUTABLE,
		SCRIPTS.get(0), # gen_locales_po.py
		POT_FILE,  # program pot file
		meson.current_source_dir(), # where to save generated po files
		'@OUTPUT@', # name of the lingua with generated po files
		msginit_executable, # native path of msginit
		langs.length().to_string(), # number of langs
		langs, # actual list of langs
	]
)


locale_dep += custom_target (
	'sources-mo',
	output: 'MO_FILES',
	command: [
		PYTHON_EXECUTABLE,
		SCRIPTS.get(1), # gen_locales_mo.py
		msgfmt_executable, # native path of msgfmt
		PROGRAM_NAME, # program name
		meson.current_source_dir(), # directory with *.po
		meson.current_build_dir(), # output directory for translations: lang/LC_MESSAGES/program.mo
		'@OUTPUT@' # dummy dep for our program
	]
)

if FS.is_file(DESKTOP_IN.full_path())

	locale_dep += custom_target(
		'create-desktop',
		input: DESKTOP_IN,
		output: PROGRAM_NAME + '.desktop',
		command :  [
			msgfmt_executable,
			'--desktop',
			'--template=@INPUT@',
			'-d',
			meson.current_source_dir(),
			'-o',
			'@OUTPUT@'
		]
	)

endif

run_target(
	'update-mo',
	command: ['rm', locale_dep]
)

run_target(
	'update-po',
	command: [
		PYTHON_EXECUTABLE,
		SCRIPTS.get(2), # gen_updated_locales_po.py
		msgmerge_executable, # native path of msgmerge
		POT_FILE, # updated program pot file
		meson.current_source_dir(), # where to save generated po files
		meson.current_build_dir() / 'LINGUAS', # overwrite file with then new languages
		langs.length().to_string(), # number of langs
		langs, # actual list of langs
	]
)

PROGRAM_I18N_DEPS += locale_dep

'''
Notes:	
run_target(
	'create-mo',
	command : ['echo', ''],
	depends: locale_dep
)
'''
