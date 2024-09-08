# locale

linguas_file = files('LINGUAS')
langs = FS.read(linguas_file).strip().split('\n')
po_files = []

if ENABLE_I18L

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

po_files_updated = []
clean_locales = []

endif

foreach lang: langs

	lang_po = lang + '.po'

	if ENABLE_I18L
		
		po_path = meson.current_source_dir() / lang_po
			
		po_file = custom_target(
			input: program_pot,
			output: lang_po,
			command: [
				PYTHON_EXECUTABLE,
				SCRIPTS.get(0), # gen_po_files.py
				meson.project_build_root() / '@INPUT@',
				meson.current_source_dir(),
				lang,
				msginit_executable,
				'@OUTPUT@'
			]
		)
		
		 mo_file = custom_target(
			output: lang + '.mo',
			input: [program_pot, po_path],
			command: [
				PYTHON_EXECUTABLE,
				SCRIPTS.get(1), # gen_mo_files.py
				msgfmt_executable,
				'@INPUT1@',
				meson.current_build_dir() / lang / 'LC_MESSAGES' / PROGRAM_NAME + '.mo',
				'@OUTPUT@'
			]
		)
		
		po_file_updated = custom_target(
			input: program_pot,
			output: 'updated-' + lang_po,
			depends: program_pot,
			build_always_stale: true,
			command: [
				PYTHON_EXECUTABLE,
				SCRIPTS.get(2), # gen_updated_po.py
				msgmerge_executable,
				'@INPUT@',
				po_path,
				'@OUTPUT@'
			]
		)
		
		po_files += po_file
		po_files_updated += po_file_updated
		I18N_DEPS += mo_file
		
		clean_locales += [
			po_path,
			po_file.full_path(),
			mo_file.full_path(),
			meson.current_build_dir() / lang,
			po_file_updated.full_path()
		]
	
	else
	
		po_files += custom_target(
			output: lang_po,
			command: [
				PYTHON_EXECUTABLE,
				SCRIPTS.get(5), # touch_me.py
				meson.current_source_dir(),
				'@OUTPUT@'
			]
		)
	
	endif
		
endforeach

if ENABLE_I18L

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
	
	run_target(
		'locales',
		depends: [program_pot, po_files],
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(4), # locales_uncleanup.py
			'.locales_uncleanup'
		]
	)
	
	run_target(
		'update-locales',
		depends: [program_pot, po_files_updated], 
		command: ['echo', '']
	)
	
	run_target(
		'clean-all-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(3), # locales_cleanup.py
			'.locales_uncleanup',
			clean_locales,
			program_pot
		]
	)
	
	run_target(
		'clean-locales',
		command: [
			PYTHON_EXECUTABLE,
			SCRIPTS.get(3), # locales_cleanup.py
			'.locales_uncleanup',
			clean_locales
		]
	)

else
	
	run_target('init-locales', depends: po_files, command: ['echo', ''])
	
endif