# .

# rsync -arvu --delete --delete-excluded --exclude=build/ unzipped/ unstable/
# rsync -arvu --delete --delete-excluded --exclude=build/ unstable/ stage/
# rsync -arvu --delete --delete-excluded --exclude=build/ stage/ blueprint-6-0/

# meson setup build [--reconfigure]
# meson compile -C build [run]

# i18n:
# to add/remove langs:
# edit LINGUAS as need it, then:
# meson setup build --reconfigure
# regenerate POTFILES with sources files:
# meson compile -C build potfiles
# extract strings from sources:
# meson compile -C build blueprint-update-po
# edit po files as need it, then build:
# meson compile -C build

project('blueprint', 'c', version: '6.0.0.2', default_options: ['c_std=gnu17,c17', 'warning_level=3'])

IS_WIN = (build_machine.system() == 'windows') ? true : false

touch_bin = find_program('touch', required: false)
if touch_bin.found()
  TOUCH_CMD = touch_bin
  SH_CMD = ['sh', '-c']
else
  TOUCH_CMD = 'echo. >'
  SH_CMD = ['cmd', '/C']
endif

FS = import('fs')

gtk4_dep         = dependency('gtk4', 'gmdule-2.0')

PROGRAM_GTK_CSD  = get_option('USE_GTK_CSD')

PROGRAM_NAME     = meson.project_name()
PROGRAM_VERSION  = meson.project_version()
PROGRAM_DESC     = 'Gtk4 application demo'
version_token    = PROGRAM_VERSION.split('.')
PROGRAM_BIN_NAME = '@0@-@1@-@2@'.format(PROGRAM_NAME, version_token[0], version_token[1])
PROGRAM_ID       = f'gtkmm4.aullidolunar.@PROGRAM_NAME@'
PROGRAM_RC_PATH  = '/@0@'.format(PROGRAM_ID.replace('.', '/'))
PROGRAM_TITLE    = f'@PROGRAM_NAME@ @PROGRAM_VERSION@'
PROGRAM_DEFS     = [
  f'-DPROGRAM_NAME="@PROGRAM_NAME@"',
  f'-DPROGRAM_VERSION="@PROGRAM_VERSION@"',
  f'-DPROGRAM_TITLE="@PROGRAM_TITLE@"',
  f'-DPROGRAM_ID="@PROGRAM_ID@"',
  f'-DPROGRAM_RC_PATH="@PROGRAM_RC_PATH@"',
  f'-DPROGRAM_GTK_CSD="@PROGRAM_GTK_CSD@"'
]

if get_option('USE_CAIRO')
  PROGRAM_DEFS   += f'-DWITH_CAIRO'
endif

if meson.get_compiler('c').get_id() == 'gcc'
	PROGRAM_DEFS   += [
		'-Wno-pedantic',
		'-Wno-overlength-strings'
	]
endif

if get_option('USE_CAIRO')
	PROGRAM_DEFS += '-DWITH_CAIRO'
endif

PROGRAM_SOURCES  = []
I18N_SOURCES     = []
I18N_DEPS        = []
PROGRAM_INCDIRS  = []

subdir('src')
subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_BIN_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: gtk4_dep,
  c_args: PROGRAM_DEFS,
  include_directories: PROGRAM_INCDIRS,
  native: true,
  export_dynamic: true
)

run_target(
	'run',
	command: [
    program_executable
  ]
)

zip_path = find_program('7z', required: false)

if zip_path.found()
  project_dir = FS.parent(meson.project_build_root())
  build_dir = FS.name(meson.current_build_dir())
  run_target(
    'zip',
    command: [
      zip_path,
      'a',
      '-t7z',
      '-xr!@0@'.format(build_dir),
      f'@PROGRAM_NAME@-@PROGRAM_VERSION@-src.7z',
      project_dir
    ]
  )
endif
