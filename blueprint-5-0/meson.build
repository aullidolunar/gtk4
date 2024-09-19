# .

# Warning!!!
# if you are testing with cmake and meson build systems, even OSs, POTFILES may have different sources paths.
# To keep meson happy:
# meson setup meson_build -DENABLE_MAINTAINER=true --reconfigure
# see if POTFILES has meson build paths, then:
# meson setup meson_build -DENABLE_MAINTAINER=false --reconfigure
#

# meson setup meson_build
# ninja -C meson_build [run] || meson compile -C meson_build [run]
# meson setup build --reconfigure

# i18n:
# edit LINGUAS as need it. Then:
# meson setup meson_build -DENABLE_MAINTAINER=true --reconfigure
# see if LINGUAS and POTFILES are written correctly. Then:
# meson setup meson_build -DENABLE_MAINTAINER=false --reconfigure
# meson compile -C meson_build blueprint-update-po
# Edit po files as need it. Then:
# meson compile -C meson_build [run]

project('blueprint', 'c', version : '5.0.0.1', default_options : ['warning_level=3'])

gtk4_dep         = dependency('gtk4', 'gmdule-2.0')

BUILD_SYS        = 'Meson Build ' + meson.version()
PROGRAM_DEPS     = [gtk4_dep]
PROGRAM_NAME     = meson.project_name()
PROGRAM_VERSION  = meson.project_version()
PROGRAM_TITLE    = PROGRAM_NAME + ' ' + PROGRAM_VERSION
PROGRAM_DESC     = 'Compile using Gtk ' + gtk4_dep.version() + ' and build with %s'
version_str      = PROGRAM_VERSION.split('.')
BIN_NAME         = PROGRAM_NAME + '-' + version_str[0] + '-' + version_str[1]
PROGRAM_ID       = 'gtk4.aullidolunar.' + PROGRAM_NAME
PROGRAM_RES_PATH = '/' + PROGRAM_ID.replace('.', '/')

PROGRAM_DEFS    = [
	'-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
	'-DGETTEXT_PACKAGE="' + PROGRAM_NAME + '"',
	'-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"',
	'-DPROGRAM_ID="' + PROGRAM_ID + '"',
	'-DPROGRAM_RESOURCE_PATH="' + PROGRAM_RES_PATH + '"',
	'-DUSE_GTK_CSD="' + get_option('USE_GTK_CSD') + '"',
	'-Wno-overlength-strings'
]

if get_option('USE_CAIRO')
	PROGRAM_DEFS += ['-DWITH_CAIRO']
endif

FS = import('fs')

PROGRAM_SOURCES = []
I18N_SOURCES    = []
I18N_DEPS       = []

IS_WIN = (build_machine.system() == 'windows') ? true : false

subdir('src')
subdir('data')
subdir('scripts')
subdir('locale')

bin_path = executable(
	BIN_NAME,
	PROGRAM_SOURCES,
	I18N_DEPS,
	dependencies: PROGRAM_DEPS,
	c_args: PROGRAM_DEFS,
	native: true,
	export_dynamic: true
)

run_target(
	'run',
	command: bin_path
)

zip_path = find_program('7z')

project_dir = FS.parent(meson.project_build_root())
project_channel = FS.stem(project_dir)

run_target('zip', command: [zip_path, 'a', '-t7z', '-xr!*_build' , project_channel + '.7z', project_dir])
