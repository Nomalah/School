set(CODE_FILES
    main.c
    src/manip.c
)

set(HEADER_FILES
    include/manip.h
)

add_executable(template ${CODE_FILES} ${HEADER_FILES})
target_include_directories(template
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
set_target_properties(template
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/$<0:>
)