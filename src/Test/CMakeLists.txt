###############################################################################
# This CMakeLists.txt contains the build and ctest configuration of the 
# unit tests.
###############################################################################

set(TARGET_NAME ReefUnitTests)

###############################################################################
# Create the Unit tests executable
###############################################################################

add_executable(${TARGET_NAME})

set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Definition of all source files
set(COMMON_SOURCES
    ${SOURCE_DIR}/Common/TypeNameTests.cpp
    ${SOURCE_DIR}/Common/HiveTests.cpp
    ${SOURCE_DIR}/Common/VisitorTests.cpp
)

# Add the test source files
target_sources(${TARGET_NAME} 
    PRIVATE ${COMMON_SOURCES})

###############################################################################
# Link the test executable
###############################################################################

#find_package(Catch2 REQUIRED)

target_link_libraries(${TARGET_NAME}
    PRIVATE
        Common
        Catch2::Catch2WithMain
)

###############################################################################
# Setup CTest
###############################################################################

include(CTest)
#catch_discover_tests(${TARGET_NAME} WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/$<CONFIG>)
