# .

# meson setup build
# ninja -C build [run] || meson compile -C build [run]
# meson setup build --reconfigure

# i18n:
# edit LINGUAS as need it. Then:
# meson setup build -DENABLE_MAINTAINER=true --reconfigure
# meson compile -C build init-locales
# meson setup build -DENABLE_MAINTAINER=false --reconfigure
# meson compile -C build blueprint-pot
# meson compile -C build blueprint-update-po
# meson compile -C build blueprint-gmo

project('blueprint', 'c', version : '4.0.0.0', default_options : ['warning_level=3'])

gtk4_dep         = dependency('gtk4', 'gmdule-2.0')

PROGRAM_DEPS     = [gtk4_dep]
PROGRAM_NAME     = meson.project_name()
PROGRAM_VERSION  = meson.project_version()
PROGRAM_TITLE    = PROGRAM_NAME + ' ' + PROGRAM_VERSION
PROGRAM_DESC     = 'Compile using Gtk ' + gtk4_dep.version() + ' and build with Meson ' + meson.version()
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
if get_option('ENABLE_MAINTAINER')
	subdir('scripts')
endif
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
