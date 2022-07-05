add_custom_target(test)
set(sources all_6805_opcodes_by_name.asm all_6805_opcodes_by_value.asm cbug05.asm)
set_property(TARGET test PROPERTY SOURCES ${sources})
foreach(source ${sources})
    add_custom_command(
	TARGET test
	POST_BUILD
	COMMAND as5 ${CMAKE_CURRENT_SOURCE_DIR}/${source}
	MAIN_DEPENDENCY ${CMAKE_CURRENT_SOURCE_DIR}/${source}
    )
endforeach()
