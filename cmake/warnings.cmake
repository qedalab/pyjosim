function(compiler_flag_fallback)
    set(single_args "OUTPUT")
    set(multi_args "FLAGS")
    set(option_args "")

    cmake_parse_arguments(COMPILER_
        "${option_args}"
        "${single_args}"
        "${multi_args}"
        ${ARGN}
    )

    foreach(arg IN LIST COMPILER_FLAGS)
        check_cxx_compiler_flag(-Wall FLAG_WORKS)
        if (FLAG_WORKS)
            set(${COMPILER_OUTPUT} ${arg} PARENT_SCOPE)
            return()
        endif()
    endforeach()

    set(${COMPILER_OUTPUT} "" PARENT_SCOPE)
endfunction()

function(target_add_warnings target)
    set(options_args
        ALL
    )

    set(single_args "")
    set(multi_args "")

    cmake_parse_arguments(WARNINGS
        "${option_args}"
        "${single_args}"
        "${multi_args}"
        ${ARGN}
    )

    # All warnings
    if(WARNINGS_ALL)
        compiler_flag_fallback(OUTPUT FLAG FLAGS -Wall /Wall)
        if(FLAG STREQUAL "")
            message(WARNING "Unable to set all warnings on target")
        else()
            target_compile_options(${target} PRIVATE ${FLAG})
        endif()
    endif()

    # All warnings
    if(WARNINGS_ALL)
        compiler_flag_fallback(OUTPUT FLAG FLAGS -Wall /Wall)
        if(FLAG STREQUAL "")
            message(WARNING "Unable to set all warnings on target")
        else()
            target_compile_options(${target} PRIVATE ${FLAG})
        endif()
    endif()
endfunction()
