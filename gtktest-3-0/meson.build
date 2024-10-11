# .

# rsync -arvu --delete --delete-excluded --exclude=_build/ unzipped/ unstable/
# rsync -arvu --delete --delete-excluded --exclude=_build/ unstable/ stage/
# rsync -arvu --delete --delete-excluded --exclude=_build/ stage/ gtktest-3-0/

# meson setup _build [--reconfigure]
# meson compile -C _build [run]

# i18n:
# to add/remove langs:
# edit LINGUAS as need it, then:
# meson setup _build --reconfigure
# regenerate POTFILES with sources files:
# meson compile -C _build potfiles
# extract strings from soueces:
# meson compile -C _build gtktest-update-po
# edit po files as need it, then build:
# meson compile -C _build

project('gtktest', 'c', version: '3.0.0.0', default_options: ['c_std=gnu17,c17', 'warning_level=3'])

IS_WIN = (build_machine.system() == 'windows') ? true : false

touch_bin = find_program('touch', required: false)
if touch_bin.found()
  TOUCH_CMD = touch_bin
  ECHO_CMD = ['sh', '-c']
else
  TOUCH_CMD = 'echo. >'
  ECHO_CMD = ['cmd', '/C']
endif

FS = import('fs')

gtk4_dep         = dependency('gtk4')

PROGRAM_GTK_CSD  = get_option('USE_GTK_CSD')

PROGRAM_NAME     = meson.project_name()
PROGRAM_VERSION  = meson.project_version()
PROGRAM_DESC     = 'Gtk4 application demo'
version_token    = PROGRAM_VERSION.split('.')
PROGRAM_BIN_NAME = '@0@-@1@-@2@'.format(PROGRAM_NAME, version_token[0], version_token[1])
PROGRAM_ID       = f'gtkmm4.aullidolunar.@PROGRAM_NAME@'
PROGRAM_RC_PATH  = '/@0@'.format(PROGRAM_ID.replace('.', '/'))
PROGRAM_DEFS     = [
  f'-DPROGRAM_NAME="@PROGRAM_NAME@"',
  f'-DPROGRAM_VERSION="@PROGRAM_VERSION@"',
  f'-DPROGRAM_DESC="@PROGRAM_DESC@"',
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

subdir('src')
subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_BIN_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: gtk4_dep,
  c_args: PROGRAM_DEFS,
  native: true
)

run_target(
	'run',
	command: [
    program_executable
  ]
)

zip_path = find_program('7z')

project_dir = FS.parent(meson.project_build_root())

run_target(
  'zip',
  command: [
    zip_path,
    'a',
    '-t7z',
    '-xr!*_build',
    f'@PROGRAM_NAME@-@PROGRAM_VERSION@-src.7z',
    project_dir
  ]
)
