# src

MesonHelperC = configure_file(
  input: 'MesonHelper.c.in',
  output: '@BASENAME@',
  configuration: {
    'PROGRAM_DESC': PROGRAM_DESC,
    'TOOLKIT_VERSION': TOOLKIT_VERSION,
    'MESON_VERSION': MESON_VERSION,
	'cero': '@0@',
	'uno': '@1@'
  }
)

sources = ['main.c', 'callbacks.c', MesonHelperC.full_path()]
PROGRAM_SOURCES += files(sources)

foreach src: sources
	I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_INCDIRS += include_directories('.')