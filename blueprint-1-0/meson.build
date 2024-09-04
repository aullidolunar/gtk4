# .

# mkdir build
# cd build
# meson setup
# ninja [run]

# meson setup --reconfigure

# i18n:

# add/remove locales from LINGUAS:
# ninja clean-all-locales
# edit LINGUAS as need it, then:
# meson setup --reconfigure
# extract strings from sources: *.{c, desktop.in, glade} with
# ninja linguas
# update the po files as need it then compile program with
# ninja [run]

# to just add/change strings in the sources without changing LINGUAS:
# make the changes in sources, then:
# ninja update-linguas
# update the po files as need it then compile program with
# ninja [run]

project('blueprint', 'c', version : '1.0.0.0', default_options : ['warning_level=3'])

gtk4_dep        = dependency('gtk4', 'gmdule-2.0')

PROGRAM_DEPS    = [gtk4_dep]
PROGRAM_NAME    = meson.project_name()
PROGRAM_VERSION = meson.project_version()
PROGRAM_TITLE   = PROGRAM_NAME + ' ' + PROGRAM_VERSION
PROGRAM_DESC    = 'Using Gtk ' + gtk4_dep.version() + ' and build with Meson ' + meson.version()

version_str     = PROGRAM_VERSION.split('.')
BIN_NAME        = PROGRAM_NAME + '-' + version_str[0] + '-' + version_str[1]

PROGRAM_ID      = 'gtk4.aullidolunar.' + PROGRAM_NAME

PROGRAM_DEFS    = [
	'-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
	'-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"',
	'-DPROGRAM_ID="' + PROGRAM_ID + '"',
	'-Wno-overlength-strings'
]

if get_option('USE_CAIRO')
	PROGRAM_DEFS += ['-DWITH_CAIRO']
endif

PROGRAM_DEFS += ['-DUSE_GTK_CSD="' + get_option('USE_GTK_CSD') + '"']

FS = import('fs')

PROGRAM_SOURCES = []
I18N_SOURCES = []
I18N_DEPS = []

IS_WIN = (build_machine.system() == 'windows') ? true : false

subdir('src')
subdir('data')
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

run_target('run', command : bin_path)

zip_path = find_program('7z')

build_dir = FS.stem(meson.project_build_root())
run_target('zip', command : [zip_path, 'a', '-t7z', '-xr!' + build_dir, BIN_NAME + '.7z', '../../' + PROGRAM_NAME])
