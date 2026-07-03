################################################################################
# This CMakeLists.txt contains the build configuration for the Reef Editor 
# library. It contains the library definition and install configuration of the
################################################################################

set(TARGET_NAME Editor)

option(EDITOR_BUILD_SHARED_LIBRARY "Build and link ${TARGET_NAME} as a shared library" OFF)

if (EDITOR_BUILD_SHARED_LIBRARY)
    set(EDITOR_BUILD_TYPE SHARED)
else()
    set(EDITOR_BUILD_TYPE STATIC)
endif()

add_library(${TARGET_NAME} ${EDITOR_BUILD_TYPE})

# The source location of the public Editor headers
set(EDITOR_PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/public/include/${TARGET_NAME})
# The source location of the private Editor headers
set(EDITOR_PRIVATE_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/private/include/${TARGET_NAME})
# The source location of the Editor library
set(EDITOR_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/private/src/${TARGET_NAME})

set(EDITOR_PUBLIC_HEADERS
    ${EDITOR_PUBLIC_INCLUDE_DIR}/Editor.hpp
    ${EDITOR_PUBLIC_INCLUDE_DIR}/EditorApplication.hpp
    ${EDITOR_PUBLIC_INCLUDE_DIR}/Inspector.hpp
    ${EDITOR_PUBLIC_INCLUDE_DIR}/SceneInspector.hpp)

set(EDITOR_PRIVATE_HEADERS
    ${EDITOR_PRIVATE_INCLUDE_DIR}/EditorCamera.hpp
    ${EDITOR_PRIVATE_INCLUDE_DIR}/EntityInspector.hpp
    ${EDITOR_PRIVATE_INCLUDE_DIR}/ScalarInspector.hpp
    ${EDITOR_PRIVATE_INCLUDE_DIR}/StringInspector.hpp)

set(EDITOR_SOURCES
    ${EDITOR_SRC_DIR}/Editor.cpp
    ${EDITOR_SRC_DIR}/EditorCamera.cpp
    ${EDITOR_SRC_DIR}/EditorApplication.cpp
    ${EDITOR_SRC_DIR}/Inspector.cpp
    ${EDITOR_SRC_DIR}/EntityInspector.cpp
    ${EDITOR_SRC_DIR}/ScalarInspector.cpp
    ${EDITOR_SRC_DIR}/SceneInspector.cpp
    ${EDITOR_SRC_DIR}/StringInspector.cpp)

###############################################################################
# Create the Editor library
###############################################################################

coral_configure_target(${TARGET_NAME}
    PUBLIC_HEADERS
        ${EDITOR_PUBLIC_HEADERS}
    PRIVATE_HEADERS
        ${EDITOR_PRIVATE_HEADERS}
    SOURCES
        ${EDITOR_SOURCES}
    PUBLIC_DEPENDENCIES
        Engine)

###############################################################################
# Organize files in the IDE
###############################################################################

source_group("public/include/Editor/" FILES  ${EDITOR_PUBLIC_HEADERS})
source_group("private/include/Editor/" FILES  ${EDITOR_PRIVATE_HEADERS})
source_group("private/src/Editor/" FILES ${EDITOR_SOURCES})
