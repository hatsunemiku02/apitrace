    # opengl32_optim.dll


    set (CMAKE_INCLUDE_CURRENT_DIR ON)

    include_directories (
        ${CMAKE_SOURCE_DIR}/helpers
        ${CMAKE_BINARY_DIR}/dispatch
        ${CMAKE_SOURCE_DIR}/dispatch
        ${CMAKE_SOURCE_DIR}/lib/guids
        ${CMAKE_SOURCE_DIR}/thirdparty/crc32c
        ${CMAKE_SOURCE_DIR}/wrappers
    )


if (WIN32)
    add_custom_command (
        OUTPUT wgltrace_optim.cpp
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/wgltrace_optim.py > ${CMAKE_CURRENT_BINARY_DIR}/wgltrace_optim.cpp
        DEPENDS
                wgltrace_optim.py
                gltrace_optim.py
                trace_optim.py
                ${CMAKE_SOURCE_DIR}/wrappers/dlltrace.py
                ${CMAKE_SOURCE_DIR}/dispatch/dispatch.py
                ${CMAKE_SOURCE_DIR}/specs/wglapi.py
                ${CMAKE_SOURCE_DIR}/specs/wglenum.py
                ${CMAKE_SOURCE_DIR}/specs/glapi.py
                ${CMAKE_SOURCE_DIR}/specs/glparams.py
                ${CMAKE_SOURCE_DIR}/specs/gltypes.py
                ${CMAKE_SOURCE_DIR}/specs/winapi.py
                ${CMAKE_SOURCE_DIR}/specs/stdapi.py
    )
    add_library (wgltrace_optim MODULE ${CMAKE_SOURCE_DIR}/wrappers/opengl32.def
        wgltrace_optim.cpp
        application.cpp
        application.h
        context.cpp
        context.h
 	drawcall.cpp
        drawcall.h
	pipeline.cpp
        pipeline.h
	state.cpp
        state.h
        predef.cpp
 	predef.h
        shaderparam.h
        shaderparam.cpp
        log.cpp
        log.h
        ${CMAKE_SOURCE_DIR}/wrappers/glproc_gl.cpp
    )
    add_dependencies (wgltrace_optim glproc)
    target_link_libraries (wgltrace_optim
        gltrace_common
        glproc
        gdi32
    )
    set_target_properties (wgltrace_optim PROPERTIES
        PREFIX ""
        OUTPUT_NAME opengl32
    )
    install (TARGETS wgltrace_optim LIBRARY DESTINATION ${WRAPPER_INSTALL_DIR})
    install_pdb (wgltrace_optim DESTINATION ${WRAPPER_INSTALL_DIR})
endif ()

if (ENABLE_EGL AND NOT WIN32 AND NOT APPLE)
    # libEGL.so/libGL.so
    add_custom_command (
        OUTPUT egltrace_optim.cpp
        COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/egltrace_optim.py > ${CMAKE_CURRENT_BINARY_DIR}/egltrace_optim.cpp
        DEPENDS
            egltrace_optim.py
            gltrace_optim.py
            trace_optim.py
            ${CMAKE_SOURCE_DIR}/dispatch/dispatch.py
            ${CMAKE_SOURCE_DIR}/specs/eglapi.py
            ${CMAKE_SOURCE_DIR}/specs/eglenum.py
            ${CMAKE_SOURCE_DIR}/specs/glapi.py
            ${CMAKE_SOURCE_DIR}/specs/glparams.py
            ${CMAKE_SOURCE_DIR}/specs/gltypes.py
            ${CMAKE_SOURCE_DIR}/specs/stdapi.py
    )

    add_library (egltrace_optim SHARED
        egltrace_optim.cpp
        application.cpp
        application.h
        context.cpp
        context.h
        log.cpp
        log.h
        ../dlsym.cpp
        ../glproc_egl.cpp
    )

    add_dependencies (egltrace_optim glproc)

    set_target_properties (egltrace_optim PROPERTIES
        # avoid the default "lib" prefix
        PREFIX ""
    )

    target_compile_definitions (egltrace_optim PRIVATE -DEGLTRACE=1)

    target_link_libraries (egltrace_optim
        gltrace_common
        glproc
        ${CMAKE_THREAD_LIBS_INIT}
        ${CMAKE_DL_LIBS}
    )

    target_linker_version_script (egltrace_optim ${CMAKE_CURRENT_SOURCE_DIR}/../egltrace.version)

    install (TARGETS egltrace_optim LIBRARY DESTINATION ${WRAPPER_INSTALL_DIR}/optimtool)
endif ()
