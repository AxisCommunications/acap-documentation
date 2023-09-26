sources = files('axoverlayexample_cairo.c')

all_cppcheck_sources += sources

install_data(sources, install_dir: axo1_example_source_install_dir)

executable('axo1_cairo',
    sources,
    install: true,
    dependencies: [axo1_dep, glib_dep, cairo_dep])
