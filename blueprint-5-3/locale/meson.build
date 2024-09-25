# locale

# Read locales:
langs = FS.read('LINGUAS').strip().split(' ')

po_paths = []
foreach lang: langs

	po_file = meson.current_source_dir() / lang + '.po'
	po_paths += po_file
	
	if not FS.exists(po_file)
		
		run_command(
			PYTHON_EXECUTABLE,
			PY_SCRIPTS[0], # touch.py
			po_file,
			check: false
		)

	endif

endforeach

# Save current source files with translatable strings in POTFILES:
run_command(
	PYTHON_EXECUTABLE,
	PY_SCRIPTS[1], # potfiles.py
	meson.current_source_dir(),
	I18N_SOURCES,
	check: false
)

i18n = import('i18n')
	
gettext = i18n.gettext(
	meson.project_name(),
	args: [
		'--from-code=UTF-8',
		'--msgid-bugs-address="aullidolunar@gmail.com"',
		'--package-version="' + PROGRAM_VERSION + '"'
	]
)

desktopfile_in = custom_target(
	input: [DESKTOP_FILE_IN, po_paths],
	output: PROGRAM_NAME + '.desktop.in',
	command: [
		'msgfmt',
		'--desktop',
		'--template=@INPUT0@',
		'-d',
		meson.current_source_dir(),
		'-o',
		'@OUTPUT@'
	]
)

desktopfile = custom_target(
	input: desktopfile_in,
	output: '@BASENAME@',
	command: [
		PYTHON_EXECUTABLE,
		PY_SCRIPTS[2], # desktop.py
		'@INPUT@',
		gtk4_dep.version(),
		meson.version(),
		'@OUTPUT@'
	]
)

# build mo files and generate desktop file with executable:
I18N_DEPS += [gettext[0], desktopfile]
