function(SetLibDirs _target)
    message("SetLibDirs for ${_target}")
    set_target_properties(${_target} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/static
    )
    if(WIN32)
        set_target_properties(${_target} PROPERTIES
            RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/shared
        )
    else()
        set_target_properties(${_target} PROPERTIES
            LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/shared
        )
    endif()
endfunction()
