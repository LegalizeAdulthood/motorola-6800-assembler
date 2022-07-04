include(CheckIncludeFile)
check_include_file(unistd.h HAVE_UNISTD_H)
check_include_file(io.h HAVE_IO_H)
configure_file(config.h.in config.h)

add_library(asm
    as.cpp
    as.h
    do.h
    eval.cpp
    eval.h
    ffwd.cpp
    ffwd.h
    globals.cpp
    globals.h
    output.cpp
    output.h
    pseudo.cpp
    pseudo.h
    symtab.cpp
    symtab.h
    table.h
    util.cpp
    util.h
    ${CMAKE_CURRENT_BINARY_DIR}/config.h
)
target_include_directories(asm PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

function(add_assembler suffix)
    add_executable(as${suffix} do${suffix}.cpp table${suffix}.cpp)
    target_link_libraries(as${suffix} PUBLIC asm)
endfunction()

add_assembler(0)
add_assembler(1)
add_assembler(4)
add_assembler(5)
add_assembler(9)
add_assembler(11)
