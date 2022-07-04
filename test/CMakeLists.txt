add_custom_target(test)
set_property(TARGET test PROPERTY SOURCES all_6805_opcodes_by_name.asm;all_6805_opcodes_by_value.asm)
add_custom_command(
    TARGET test
    POST_BUILD
    COMMAND as5 ${CMAKE_CURRENT_SOURCE_DIR}/all_6805_opcodes_by_name.asm
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/all_6805_opcodes_by_name.asm
)
add_custom_command(
    TARGET test
    POST_BUILD
    COMMAND as5 ${CMAKE_CURRENT_SOURCE_DIR}/all_6805_opcodes_by_value.asm
    MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/all_6805_opcodes_by_value.asm
)
