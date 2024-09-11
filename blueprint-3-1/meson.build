# .

# mkdir build
# cd build
# meson setup
# ninja [run]

# meson setup build
# ninja -C build [run]
# meson setup build --reconfigure

# i18n:

# to add/remove locales from LINGUAS first:
# backup current po files:
# ninja -C build backup-locales || meson compile -C build backup-locales
# If not, we need to start all over again translating :/
# Remove current locales with
# ninja -C build clean-locales
# edit LINGUAS as need it, then:
# meson setup build --reconfigure
# generate or restore backed-up po templates with:
# ninja -C build init-locales
# extract strings from sources: *.{c, desktop.in, glade} to update po files as need it with
# ninja -C build update-locales
# translate the po files as need it then create mo files with:
# ninja -C build [run]

# to just add/change strings in the sources without changing LINGUAS:
# make the changes in sources, then:
# ninja -C build update-locales
# translate the po files as need it then create mo files with:
# ninja -C build [run]

# no i18n?
# meson setup -DUSE_LOCALE=false build --reconfigure

project('blueprint', 'c', version : '3.1.0.0', default_options : ['warning_level=3'])

gtk4_dep        = dependency('gtk4', 'gmdule-2.0')

PROGRAM_DEPS    = [gtk4_dep]
PROGRAM_NAME    = meson.project_name()
PROGRAM_VERSION = meson.project_version()
PROGRAM_TITLE   = PROGRAM_NAME + ' ' + PROGRAM_VERSION
PROGRAM_DESC    = 'Using Gtk ' + gtk4_dep.version() + ' and build with Meson ' + meson.version()
version_str     = PROGRAM_VERSION.split('.')
BIN_NAME        = PROGRAM_NAME + '-' + version_str[0] + '-' + version_str[1]
PROGRAM_ID      = 'gtk4.aullidolunar.' + PROGRAM_NAME
PROGRAM_RESOURCE_PATH = '/' + PROGRAM_ID.replace('.', '/')

PROGRAM_DEFS    = [
	'-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
	'-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"',
	'-DPROGRAM_ID="' + PROGRAM_ID + '"',
	'-DPROGRAM_RESOURCE_PATH="' + PROGRAM_RESOURCE_PATH + '"',
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

ENABLE_I18L = get_option('USE_LOCALE')

if ENABLE_I18L
	PROGRAM_DEFS += ['-DENABLE_I18L']
endif

message('ENABLE_I18L=' + ENABLE_I18L.to_string())

subdir('src')
subdir('scripts')
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

run_target(
	'run',
	command: bin_path
)

zip_path = find_program('7z')

build_dir = FS.stem(meson.project_build_root())
project_dir = FS.parent(meson.project_build_root())
project_channel = FS.stem(project_dir)

run_target('zip', command: [zip_path, 'a', '-t7z', '-xr!' + build_dir, project_channel + '.7z', project_dir])
