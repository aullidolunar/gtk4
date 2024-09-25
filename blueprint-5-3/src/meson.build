# src

sources = ['main.c', 'callbacks.c']
PROGRAM_SOURCES += files(sources)

foreach src: sources
	I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach
