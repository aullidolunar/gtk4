# .

# cd build
# meson setup
# meson compile
# meson setup --reconfigure

# i18n:
# meson compile create-pot
# meson compile create-po | meson compile update-po

project('xfSoundThemei18n', 'c', version : '1.0.0.3', default_options : ['warning_level=3'])

PROGRAM_DEFS = ['-DPROGRAM_NAME="' + meson.project_name() + '"', '-Wno-overlength-strings']

if get_option('USE_CAIRO')
	PROGRAM_DEFS += ['-DWITH_CAIRO']
endif

if get_option('USE_GTK_CSD')
	gtk_csd = '1'
else
	gtk_csd = '0'
endif

PROGRAM_DEFS += ['-DUSE_GTK_CSD="' + gtk_csd + '"']

# for stem, is_file, read
fs = import('fs')

version_str =  meson.project_version().split('.')

BIN_NAME = meson.project_name() + '-' + version_str[0] + '-' + version_str[1]

gtk4_dep = dependency('gtk4')

PROGRAM_DEPS = [gtk4_dep]

if build_machine.system() != 'windows'
	xfconf_dep = dependency('libxfconf-0')
	PROGRAM_DEPS += xfconf_dep
endif

PROGRAM_DESC = 'Program compile with Gtk4 ' + gtk4_dep.version()
PROGRAM_SOURCES = []
SOURCES_I18N = []
POT_FILES = []

subdir('src')
subdir('data')
subdir('locales')

bin_path = executable(
	BIN_NAME,
	PROGRAM_SOURCES, mo_files,
	dependencies : PROGRAM_DEPS,
	c_args: PROGRAM_DEFS,
	native: true
)

run_target('run', command : bin_path)

zip_path = find_program('7z')

build_dir = fs.stem(meson.project_build_root())
run_target('zip', command : [zip_path, 'a', '-t7z', '-xr!' + build_dir, BIN_NAME + '.7z', '../../' + meson.project_name()])
