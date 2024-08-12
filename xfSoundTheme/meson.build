# .

# meson setup build
# cd build
# ninja | meson compile
# meson setup --reconfigure

project('xfSoundTheme', 'c', version : '1.0.0.0', default_options : ['warning_level=3'])

version_str =  meson.project_version().split('.')

bin_name = meson.project_name() + '-' + version_str[0] + '-' + version_str[1]

gtk_dep = dependency('gtk4')
xfconf_dep = dependency('libxfconf-0')

PROGRAM_DESC = 'Programa basado en Gtk4 ' + gtk_dep.version()

progdefs = ['-DPROGRAM_NAME="' + meson.project_name() + '"', '-Wno-overlength-strings']

if get_option('USE_CAIRO')
	progdefs += ['-DWITH_CAIRO']
endif

if get_option('USE_GTK_CSD')
	gtk_csd = '1'
else
	gtk_csd = '0'
endif

progdefs += ['-DUSE_GTK_CSD="' + gtk_csd + '"']

PROGRAM_SOURCES = []
PROGRAM_DEPS = [gtk_dep, xfconf_dep]
PROGRAM_INCLUDE_DIRS = []

subdir('src')
subdir('data')

bin_path = executable(
	bin_name,
	PROGRAM_SOURCES,
	dependencies : PROGRAM_DEPS,
	include_directories : PROGRAM_INCLUDE_DIRS,
	c_args: progdefs,
	native: true
)

run_target('run', command : bin_path)

zip_path = find_program('7z')

# for stem
fs = import('fs')

build_dir = fs.stem(meson.project_build_root())
run_target('zip', command : [zip_path, 'a', '-t7z', '-xr!' + build_dir, bin_name + '.7z', '../../' + meson.project_name()])
