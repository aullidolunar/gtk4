# locale

xgettext_executable = find_program('xgettext')
msginit_executable = find_program('msginit')
msgfmt_executable = find_program('msgfmt')
msgmerge_executable = find_program('msgmerge')

program_pot = custom_target(
	'program-pot',
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

linguas_file = files('LINGUAS')
langs = FS.read(linguas_file).split('\n')

po_files_updated = []
po_files = []
mo_dir = []

clean_mo_dirs = []
clean_po_files = []

foreach lang: langs

	lang_po = lang + '.po'
	po_path = meson.current_source_dir() / lang_po
	
	clean_po_files += po_path
	
	mo_outdir = meson.current_build_dir() / lang / 'LC_MESSAGES'
	
	clean_mo_dirs += meson.current_build_dir() / lang
	
	po_files += custom_target(
		lang + '-po',
		input: program_pot,
		output: lang_po,
		command: [
			msginit_executable,
			'-l',
			lang + '.UTF-8',
			'--no-translator',
			'-o',
			po_path,
			'-i',
			'@INPUT@'
		]
	)
	
	po_files_updated += custom_target(
		lang + '-po-update',
		input: program_pot,
		output: 'updated-' + lang_po,
		depends: program_pot,
		command: [
			msgmerge_executable,
			'-U',
			'--backup=off',
			po_path,
			'@INPUT@'
		]
	)
	
	mo_dir += custom_target(
		'make-' + lang + '-mo-dir',
		output: lang,
		command: [
			'mkdir', '-p', mo_outdir
		]
	)
	
	I18N_DEPS += custom_target(
		lang + '-mo',
		depends: mo_dir,
		output: lang_po.replace('po', 'mo'),
		command: [
			msgfmt_executable,
			'-o',
			mo_outdir / '@0@.mo'.format(PROGRAM_NAME),
			po_path
		]
	)

endforeach

if FS.is_file(DESKTOP_IN.full_path())
	
	I18N_DEPS += custom_target(
		'desktop-file',
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
	'linguas',
	depends: [program_pot, po_files],
	command: ['echo', '']
)

run_target(
	'update-linguas',
	depends: [program_pot, po_files_updated], 
	command: ['echo', '']
)

run_target(
	'clean-all-locales',
	command: [
		'rm',
		'-rf',
		clean_po_files,
		clean_mo_dirs,
		program_pot
	]
)

run_target(
	'clean-locales',
	command: [
		'rm',
		'-rf',
		clean_mo_dirs,
	]
)