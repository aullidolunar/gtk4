# .

# mkdir build
# cd build
# meson setup
# ninja [run]

# i18n:
# change strings in *.c or desktop.in
# or
# add/remove languages in locale/LINGUAS, then:
# meson setup --reconfigure
# ninja create-pot
# ninja update-po
# translate strings in *.po, then:
# ninja update-mo
# ninja [run]

# update strings in *.po, then:
# ninja update-mo
# ninja [run]


project('xfSoundThemei18n', 'c', version : '1.0.0.4', default_options : ['warning_level=3'])

gtk4_dep        = dependency('gtk4')

PROGRAM_DEPS    = [gtk4_dep]
PROGRAM_NAME    = meson.project_name()
PROGRAM_VERSION = meson.project_version()
PROGRAM_TITLE   = PROGRAM_NAME + ' ' + PROGRAM_VERSION
PROGRAM_DESC    = 'Compiled with Gtk4 ' + gtk4_dep.version() + ' and Meson Build ' + meson.version()

version_str     = PROGRAM_VERSION.split('.')
BIN_NAME        = PROGRAM_NAME + '-' + version_str[0] + '-' + version_str[1]

PROGRAM_DEFS    = [
	'-DPROGRAM_NAME="' + PROGRAM_NAME + '"',
	'-DPROGRAM_TITLE="' + PROGRAM_TITLE + '"',
	'-Wno-overlength-strings'
]

if get_option('USE_CAIRO')
	PROGRAM_DEFS += ['-DWITH_CAIRO']
endif

PROGRAM_DEFS += ['-DUSE_GTK_CSD="' + get_option('USE_GTK_CSD') + '"']

if build_machine.system() != 'windows'
	PROGRAM_DEPS += dependency('libxfconf-0')
endif

# for stem, is_file, read
FS = import('fs')

PROGRAM_SOURCES = []
PROGRAM_I18N_DEPS = []
subdir('src')
subdir('data')
subdir('scripts')
subdir('locale')

bin_path = executable(
	BIN_NAME,
	PROGRAM_SOURCES,
	PROGRAM_I18N_DEPS,
	dependencies: PROGRAM_DEPS,
	c_args: PROGRAM_DEFS,
	native: true
)

run_target('run', command : bin_path)

zip_path = find_program('7z')

build_dir = FS.stem(meson.project_build_root())
run_target('zip', command : [zip_path, 'a', '-t7z', '-xr!' + build_dir, BIN_NAME + '.7z', '../../' + PROGRAM_NAME])
