Project(examples)

SET(TEST_SRC_FILE_NAMES 
                        test_htree
                        test_htree2
                        test_sha256
                        )

INCLUDE_DIRECTORIES(${INCLUDE_DIR})
FOREACH(TEST IN LISTS TEST_SRC_FILE_NAMES)

    MESSAGE(STATUS "Creating executable for ${TEST}.cpp")

    ADD_EXECUTABLE(${TEST} ${CMAKE_CURRENT_LIST_DIR}/${TEST}.cpp)
    TARGET_INCLUDE_DIRECTORIES(${TEST} PUBLIC ${INCLUDE_DIR})
    
    TARGET_LINK_LIBRARIES(${TEST} ${LIBRARIES_TO_LINK} OpenSSL::SSL)

    SET_TARGET_PROPERTIES(
        ${TEST}
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${BIN_DIR}"
    )
ENDFOREACH()