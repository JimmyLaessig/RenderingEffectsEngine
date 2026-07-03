################################################################################
# This CMakeLists.txt contains the build configuration for the Rendering module
# library. It contains the library definition and install configuration of the
################################################################################

set(TARGET_NAME Rendering)

reef_add_library(${TARGET_NAME} STATIC)

# The source location of the public headers
set(PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/Reef/${TARGET_NAME})

# The source location of the library
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PUBLIC_HEADERS
    ${PUBLIC_INCLUDE_DIR}/Renderer.hpp
    ${PUBLIC_INCLUDE_DIR}/RenderObject.hpp
    ${PUBLIC_INCLUDE_DIR}/Resource.hpp
    ${PUBLIC_INCLUDE_DIR}/IndexedGeometry.hpp
    ${PUBLIC_INCLUDE_DIR}/IndexBuffer.hpp)

set(PRIVATE_HEADERS
    ${SRC_DIR}/DefaultRendererImpl.hpp
    ${SRC_DIR}/IndexedGeometryResource.hpp
    ${SRC_DIR}/TransformResource.hpp
    ${SRC_DIR}/RenderResource.hpp
    ${SRC_DIR}/RenderObjectImpl.hpp
    ${SRC_DIR}/ShaderRegistry.hpp
    ${SRC_DIR}/ResourceManager.hpp)

set(SOURCES
    ${SRC_DIR}/RenderObjectImpl.cpp
    ${SRC_DIR}/IndexedGeometry.cpp
    ${SRC_DIR}/ShaderRegistry.cpp
    ${SRC_DIR}/IndexedGeometryResource.cpp
    ${SRC_DIR}/TransformResource.cpp
    ${SRC_DIR}/IndexBuffer.cpp
    ${SRC_DIR}/RenderResource.cpp
    ${SRC_DIR}/Resource.cpp
    ${SRC_DIR}/ResourceManager.cpp
    ${SRC_DIR}/DefaultRendererImpl.cpp)

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET public_headers
    TYPE HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES ${PUBLIC_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    FILE_SET private_headers
    TYPE HEADERS
    BASE_DIRS ${SRC_DIR}
    FILES ${PRIVATE_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    ${SOURCES})

target_link_libraries(${TARGET_NAME} PUBLIC
    glm::glm
    slang
    Util
    Coral
    CoralUtil)

coral_configure_target(${TARGET_NAME})

set(SHADERS
    ${SRC_DIR}/Shaders/Camera.slang
    ${SRC_DIR}/Shaders/Transform.slang
    ${SRC_DIR}/Shaders/SimpleVertexShader.slang
    ${SRC_DIR}/Shaders/SimpleFragmentShader.slang
)

target_sources(${TARGET_NAME} PRIVATE
    ${SHADERS})

target_embed_files(${TARGET_NAME} PRIVATE
    OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/generated/include/Shaders"
    BASE_DIRS  "${CMAKE_CURRENT_BINARY_DIR}/generated/include"
    FILE_SET   generated_headers
    FILES      ${SHADERS}
    NAMESPACE Shaders)

###############################################################################
# Organize files in the IDE
###############################################################################

source_group("include"     FILES ${PUBLIC_HEADERS})
source_group("src"         FILES ${PRIVATE_HEADERS})
source_group("src"         FILES ${SOURCES})
source_group("src/Shaders" FILES ${SHADERS})
