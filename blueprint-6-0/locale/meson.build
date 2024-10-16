# locale

i18n = import('i18n')

# Read locales:
langs = FS.read('LINGUAS').strip().split('\n')

po_paths = []
foreach lang: langs
  po_file = meson.current_source_dir() / '@0@.po'.format(lang)
  po_paths += po_file
  if not FS.exists(po_file)
    run_command(
      TOUCH_CMD,
      po_file,
      check: true
    )
  endif
endforeach

# Save current source files with translatable strings in POTFILES:
run_target(
  'potfiles',
  command: [
    SH_CMD,
    'echo -n "@0@" > "@1@"'.format('\n'.join(I18N_SOURCES), meson.current_source_dir() / 'POTFILES')
  ]
)
	
gettext = i18n.gettext(
  PROGRAM_NAME,
  preset: 'glib',
  args: [
    '--msgid-bugs-address="aullidolunar@gmail.com"',
    f'--package-name="@PROGRAM_NAME@"',
    f'--package-version="@PROGRAM_VERSION@"'
  ]
)

desktopfile = custom_target(
  input: [DESKTOP_FILE_IN, po_paths],
  output: '@BASENAME0@',
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

# build mo files and generate desktop file with executable:
I18N_DEPS += [gettext[0], desktopfile]
