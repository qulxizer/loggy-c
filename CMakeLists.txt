cmake_minimum_required(VERSION 3.11)
project(loggy VERSION 0.0.1 LANGUAGES C)

# Library
add_library(loggy SHARED src/loggy.c)
target_include_directories(loggy
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<INSTALL_INTERFACE:include>
)

# Test executable
add_executable(loggy_test test/loggy_test.c)
target_link_libraries(loggy_test PUBLIC loggy)

enable_testing()
add_test(NAME loggy_test COMMAND loggy_test)

# Install library + export set
install(TARGETS loggy
    EXPORT loggyTargets
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
    INCLUDES DESTINATION include
)

# Install all headers from src/
install(DIRECTORY src/ DESTINATION include FILES_MATCHING PATTERN "*.h")

# Install export file
install(EXPORT loggyTargets
    FILE loggyTargets.cmake
    NAMESPACE loggy::
    DESTINATION lib/cmake/loggy
)

# Minimal config file
file(WRITE ${CMAKE_BINARY_DIR}/loggyConfig.cmake
"include(\${CMAKE_CURRENT_LIST_DIR}/loggyTargets.cmake)"
)
install(FILES ${CMAKE_BINARY_DIR}/loggyConfig.cmake DESTINATION lib/cmake/loggy)

