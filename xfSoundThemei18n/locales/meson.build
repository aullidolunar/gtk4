# locales

LOCALES_FILE = 'LINGUAS'

if fs.is_file(LOCALES_FILE)

	msginit_executable = find_program('msginit')
	msgfmt_executable = find_program('msgfmt')
	msgmerge_executable = find_program('msgmerge')

	locales = fs.read(LOCALES_FILE).strip().split(' ')

	po_files = []
	mo_files = []
	updated_po = []
	desktop_files = []

	foreach loc : locales

		message('Locale to build: ' + loc)

		po_path = join_paths(meson.current_source_dir(), loc + '.po')

		po_files += custom_target(
			'create-' + loc + '-po',
			output: loc + '.po',
			command :  [
				msginit_executable,
				'-i',
				'../data/' + meson.project_name() + '.pot',
				'-l',
				loc + '.UTF-8',
				'--no-translator',
				'-o',
				po_path
			]
		)

		mo_path = meson.current_build_dir() / loc / 'LC_MESSAGES'

		lc_messages_dir = custom_target(
			'create-lc-messages-' + loc,
			output: loc + '-LC_MESSAGES',
			command : ['mkdir', '-p', mo_path]
		)

		mo_files += custom_target(
			'create-' + loc + '-mo',
			output: loc + '.mo',
			depends : lc_messages_dir,
			command :  [
				msgfmt_executable,
				po_path,
				'-o',
				mo_path / meson.project_name() + '.mo'
			]
		)

		updated_po += custom_target(
			'update-' + loc + '-po',
			output : 'updated-' + loc + '.po',
			command : [
				msgmerge_executable,
				'-U',
				'--backup=off',
				'../locales/' + loc + '.po',
				'../data/' + meson.project_name() + '.pot'
			]
		)

	endforeach

	run_target(
		'create-po',
		command : ['echo', ''],
		depends: po_files
	)

	if fs.is_file(desktop_in.full_path())
		# desktop_in
		mo_files += custom_target(
			'create-desktop',
			input: desktop_in,
			output: meson.project_name() + '.desktop',
			command :  [
				msgfmt_executable,
				'--desktop',
				'--template=@INPUT@',
				'-d',
				'../locales/',
				'-o',
				'@OUTPUT@'
			]
		)

		mo_files += desktop_files

	endif

	run_target(
		'create-mo',
		command : ['echo', ''],
		depends: mo_files
	)

	run_target(
		'update-po',
		depends : [pot_file, updated_po],
		command : ['echo', '']
	)

	PROGRAM_DEFS += ['-DLOCALEDIR="' + meson.current_build_dir() + '"']

endif
