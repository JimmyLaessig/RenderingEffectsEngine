################################################################################
# This CMakeLists.txt contains the build configuration for the Reef::Util 
# library. It contains the library definition and install configuration of the
################################################################################

set(TARGET_NAME Util)

add_library(${TARGET_NAME} INTERFACE)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/Reef/${TARGET_NAME})

set(HEADERS
    ${INCLUDE_DIR}/Export.hpp
    ${INCLUDE_DIR}/BoundingBox.hpp
    ${INCLUDE_DIR}/Camera.hpp
    ${INCLUDE_DIR}/Hive.hpp
    ${INCLUDE_DIR}/Constants.hpp
    ${INCLUDE_DIR}/TypeName.hpp
    ${INCLUDE_DIR}/CRC32.hpp
    ${INCLUDE_DIR}/Finally.hpp
    ${INCLUDE_DIR}/Intervall.hpp
    ${INCLUDE_DIR}/MemoryBlock.hpp
    ${INCLUDE_DIR}/NonCopyable.hpp
    ${INCLUDE_DIR}/NonMovable.hpp
    ${INCLUDE_DIR}/Singleton.hpp
    ${INCLUDE_DIR}/StringMap.hpp
    ${INCLUDE_DIR}/PixelFormat.hpp
    ${INCLUDE_DIR}/Visitor.hpp)

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES ${HEADERS})

target_link_libraries(${TARGET_NAME} INTERFACE
    glm::glm
    stb)

coral_configure_target(${TARGET_NAME})

###############################################################################
# Organize files in the IDE
###############################################################################

source_group("include/Reef/${TARGET_NAME}"  FILES ${HEADERS})
