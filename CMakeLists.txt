cmake_minimum_required(VERSION 4.0)
project(save_file C CXX)
set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

if ("X${CMAKE_BUILD_TYPE}" STREQUAL "XDebug")
    add_compile_definitions(DEBUG=1)
    set(compiler_options
            # Warnings and diagnostics
            -Wall                                   # Enable common warnings
            -Wextra                                 # Enable extra warnings
            -Wpedantic                              # Strict compliance with the standard
            -Wunused                                # Warn about unused variables, functions, etc.
            -Wuninitialized                         # Warn if variables are used uninitialized
            -fdiagnostics-show-option               # Show which option triggered the warning
            -fdiagnostics-color=always              # Enable colored diagnostics for better readability
            -march=native
            -mtune=native

            # Debugging and stack protection
            -g3                                     # Maximum debug information, including macro expansions
            -O0
            -gdwarf-4                               # Generate DWARF version 4 debug information
            -fno-eliminate-unused-debug-types
            -fno-omit-frame-pointer
            -Wl,-z,relro -Wl,-z,now
            -fstack-protector-all
    )

    set(linker_options
            # Linker options for memory safety, thread safety, and verbose debugging
            -Wl,--no-omagic                         # Prevent the generation of object files in memory; useful for debugging
            -Wl,--as-needed                         # Only link libraries that are actually needed to reduce binary size
            -Wl,--fatal-warnings                    # Treat all linker warnings as errors to catch issues early
            -Wl,-z,relro                            # Read-only relocations to prevent certain memory exploits (optional)
            -Wl,-z,now                              # Fully resolve all symbols during the link time for extra safety
            -Wl,-z,noexecstack                      # Prevent execution of code on the stack (security hardening)
            -Wl,-z,defs                             # Ensure all symbols are defined, and prevent undefined symbols
            -Wl,-O0

            -gdwarf-4                               # Generate detailed debug information for the linker
            -fno-eliminate-unused-debug-types
            -fno-omit-frame-pointer

            # Stack protection
            -fstack-protector-all                   # Link with stack protection for all functions
            -Wl,-z,relro -Wl,-z,now
    )

    #    list(APPEND compiler_options
    #            -fsanitize=address
    #            -fsanitize=undefined
    #    )
    #
    #    list(APPEND linker_options
    #            -fsanitize=address
    #            -fsanitize=undefined
    #            -lasan
    #            -lubsan
    #    )

    #    list(APPEND compiler_options
    #            -fsanitize=thread
    #            -fsanitize=undefined
    #    )
    #
    #    list(APPEND linker_options
    #            -fsanitize=thread
    #            -fsanitize=undefined
    #            -ltsan -lubsan
    #    )

    add_compile_options(${compiler_options})
    add_link_options(${linker_options})
else ()
    set(optimization_flags
            -O3
            -march=native
            -mtune=native
            -flto
            -fomit-frame-pointer
            -ffast-math
            -fstrict-aliasing
            -fdata-sections
            -ffunction-sections
            -fno-stack-protector
            -Wl,-z,relro -Wl,-z,now
            -fno-rtti
            -s
    )

    set(optimization_link_flags
            -O3
            -march=native
            -mtune=native
            -flto
            -fomit-frame-pointer
            -ffast-math
            -fstrict-aliasing
            -fdata-sections
            -ffunction-sections
            -Wl,--gc-sections
            -fno-stack-protector
            -Wl,-z,relro -Wl,-z,now
            -fno-rtti
            -s
    )

    add_compile_definitions(DEBUG=0)
    add_compile_options(${optimization_flags})
    add_link_options(${optimization_link_flags})
endif ()

include_directories(src/include)
add_executable(save_file
        main.cpp
        src/helpers/log.cpp         src/include/log.h
        src/include/color.h         src/helpers/color.cpp
)
