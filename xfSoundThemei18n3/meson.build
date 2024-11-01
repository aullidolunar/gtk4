# .

# rsync -arvu --delete --delete-excluded --exclude=build/ unzipped/ xfSoundThemei18n/

# meson setup build [--reconfigure]
# meson compile -C build [run]

# i18n:
# to add/remove langs:
# edit LINGUAS as need it, then:
# meson setup build --reconfigure
# regenerate POTFILES with sources files:
# meson compile -C build potfiles
# extract strings from sources:
# meson compile -C build xfSoundThemei18n-update-po
# edit po files as need it, then build:
# meson compile -C build

project('xfSoundThemei18n', 'c', version: '3.0.0.0', meson_version: '>= 1.5.0', default_options: ['c_std=gnu17,c17', 'warning_level=3'])

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

PROGRAM_DEPS = []
PROGRAM_DEPS += dependency('gtk4', version: '>= 4.10.0', required: true)

if not IS_WIN
	PROGRAM_DEPS += dependency('libxfconf-0', required: true)
endif

PROGRAM_GTK_CSD = get_option('USE_GTK_CSD')

PROGRAM_VERSION = meson.project_version()
PROGRAM_NAME    = meson.project_name()
PROGRAM_DESC    = 'Sound theme selector for xfce'
PROGRAM_ID      = f'gtk4.aullidolunar.@PROGRAM_NAME@'
PROGRAM_RC_PATH = '/@0@'.format(PROGRAM_ID.replace('.', '/'))
PROGRAM_TITLE   = f'@PROGRAM_NAME@ @PROGRAM_VERSION@'
PROGRAM_DEFS    = [
  f'-DPROGRAM_NAME="@PROGRAM_NAME@"',
  f'-DPROGRAM_VERSION="@PROGRAM_VERSION@"',
  f'-DPROGRAM_TITLE="@PROGRAM_TITLE@"',
  f'-DPROGRAM_ID="@PROGRAM_ID@"',
  f'-DPROGRAM_RC_PATH="@PROGRAM_RC_PATH@"',
  f'-DPROGRAM_GTK_CSD="@PROGRAM_GTK_CSD@"'
]

if get_option('USE_CAIRO')
  PROGRAM_DEFS += '-DWITH_CAIRO'
endif

if meson.get_compiler('c').get_id() == 'gcc'
  PROGRAM_DEFS += [
    '-Wno-pedantic',
    '-Wno-overlength-strings'
  ]
endif

PROGRAM_INCDIRS = []
PROGRAM_SOURCES = []
I18N_SOURCES    = []
I18N_DEPS       = []

subdir('src')
subdir('data')
subdir('locale')

program_executable = executable(
  PROGRAM_NAME,
  PROGRAM_SOURCES,
  I18N_DEPS,
  dependencies: PROGRAM_DEPS,
  include_directories: PROGRAM_INCDIRS,
  c_args: PROGRAM_DEFS,
  export_dynamic: true,
  native: true
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
      f'@PROGRAM_NAME@-v@PROGRAM_VERSION@-src.7z',
      project_dir
    ]
  )
endif