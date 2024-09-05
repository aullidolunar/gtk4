# src

set(SOURCE_FILES callbacks.c main.c)

target_sources(${BIN_NAME} PRIVATE ${SOURCE_FILES})

set(XGETTEXT_SOURCES ../../src/callbacks.c ../../src/main.c PARENT_SCOPE)