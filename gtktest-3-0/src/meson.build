# src

sources = files('main.c', 'callbacks.c')

foreach src: sources
	I18N_SOURCES += FS.relative_to(src, meson.project_source_root())
endforeach

PROGRAM_SOURCES += sources

# PROGRAM_INCDIRS += include_directories('.')