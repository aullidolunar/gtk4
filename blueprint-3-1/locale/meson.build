# locale

if ENABLE_I18L

	if not FS.exists('LINGUAS')
		error('"LINGUAS" file was not located in the directory: "' + meson.current_source_dir() + '".')
	endif
	
	langs = FS.read('LINGUAS').strip().split('\n')
	
	xgettext_executable = find_program('xgettext')
	msginit_executable = find_program('msginit')
	msgfmt_executable = find_program('msgfmt')
	msgmerge_executable = find_program('msgmerge')
	
	program_pot = custom_target(
		output: PROGRAM_NAME + '.pot',
		input: I18N_SOURCES,
		command: [
			xgettext_executable,
			'--from-code=UTF-8',
			'--package-name=' + PROGRAM_NAME + '',
			'--package-version=' + PROGRAM_VERSION + '',
			'--msgid-bugs-address=aullidolunar@gmail.com',
			'--copyright-holder=aullidolunar',
			'-k_',
			'-kN_',
			'-o',
			'@OUTPUT@',
			'@INPUT@'
		]
	)
	
	run_target(
		'init-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(5), # init-locales.py
			meson.current_source_dir(),
			'.dep.po'
		]
	)
	
	run_target(
		'locales',
		depends: program_pot,
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(0), # gen_po_files.py
			msginit_executable,
			program_pot,
			meson.current_source_dir(),
			langs
		]
	)
	
	run_target(
		'update-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(2), # gen_updated_po.py
			msgmerge_executable,
			program_pot,
			meson.current_source_dir()
		]
	)
	
	I18N_DEPS += custom_target(
		'mo-locales',
		output: '.dep.mo',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(1), # gen_mo_files.py
			msgfmt_executable,
			meson.current_source_dir(),
			PROGRAM_NAME,
			'@OUTPUT@'
		]
	)
		
	run_target(
		'clean-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(3), # locales_cleanup.py
			meson.current_build_dir(),
			meson.current_source_dir(),
		]
	)
	
	run_target(
		'backup-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(4), # backup_locales.py
			meson.current_source_dir()
		]
	)
	
	run_target(
		'backup-locales-no-more',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(7), # backup_locales_no_more.py
			meson.current_build_dir()
		]
	)
	
	if FS.is_file(DESKTOP_IN.full_path())
			
		I18N_DEPS += custom_target(
			input: DESKTOP_IN,
			output: PROGRAM_NAME + '.desktop',
			command: [
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

endif
