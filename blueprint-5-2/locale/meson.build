# locale

# Test for po files in the directory:
langs = FS.read('LINGUAS').strip().split(' ')
foreach lang: langs

	lang_po = lang + '.po'
	po_file = meson.current_source_dir() / lang_po
	run_command(
		PYTHON_EXECUTABLE,
		PY_SCRIPTS[0], # touch.py
		po_file,
		check: false
	)

endforeach


# Save current source files with translatable strings in POTFILES:
run_command(
	PYTHON_EXECUTABLE,
	PY_SCRIPTS[1], # potfile.py
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
	
# build mo files with executable:
I18N_DEPS += gettext[0]

if not IS_WIN
	
	if FS.exists(meson.current_build_dir() / PROGRAM_NAME + '.desktop')
		run_command(
			PYTHON_EXECUTABLE,
			PY_SCRIPTS[2], # delete.py
			meson.current_build_dir() / PROGRAM_NAME + '.desktop',
			check: false
		)
	endif
	
	I18N_DEPS += i18n.merge_file(
		input: DESKTOP_IN,
		output: PROGRAM_NAME + '.desktop',
		type: 'desktop',
		po_dir: meson.current_source_dir()
	)

endif
