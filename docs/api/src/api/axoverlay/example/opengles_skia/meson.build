sources = files('opengles_skia.cpp')

all_cppcheck_sources += sources

install_data(sources, install_dir: axo1_example_source_install_dir)

if get_option('opengl')
    skia_dep = dependency('skia', required: false)
    freetype_dep = dependency('freetype2', required: false)
    raqm_dep = dependency('raqm', required: false)
    harfbuzz_dep = dependency('harfbuzz', required: false)

    executable('axo1_opengles_skia',
        sources,
        install: true,
        dependencies: [axo1_dep, glib_dep, freetype_dep, skia_dep, raqm_dep, harfbuzz_dep, glesv2_dep])
endif
