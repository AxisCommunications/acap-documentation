sources = files(
    'config.cpp',
    'gl_example_errors.c',
    'loaders.cpp',
    'mesh.cpp',
    'opengles_objectloader.cpp',
    'render.cpp',
    'shaders.c',
)

# FIXME opengles_objectloader example is not clean in cppcheck
#all_cppcheck_sources += sources

install_data(sources, install_dir: axo1_example_source_install_dir)

if get_option('opengl')
    cxx.has_header('tiny_obj_loader.h', required: true)
    cxx.has_header('stb_image.h', required: true)

    executable('axo1_opengles_objectloader',
        sources,
        install: true,
        dependencies: [axo1_dep, glib_dep, glesv2_dep, egl_dep])
endif
