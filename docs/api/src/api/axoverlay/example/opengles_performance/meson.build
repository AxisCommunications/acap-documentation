sources = files('opengles_performance.c')

all_cppcheck_sources += sources

install_data(sources, install_dir: axo1_example_source_install_dir)

if get_option('opengl')
    executable('axo1_opengles_performance',
        sources,
        install: true,
        dependencies: [axo1_dep, glib_dep, cairo_dep, glesv2_dep])
endif
