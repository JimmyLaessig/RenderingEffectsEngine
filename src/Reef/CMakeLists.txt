################################################################################
# This CMakeLists.txt contains the build configuration for the Engine 
# library. It contains the library definition and install configuration of the
################################################################################

###############################################################################
# Create the Reef library
###############################################################################

set(TARGET_NAME Reef)



option(REEF_BUILD_SHARED_LIBRARY "Build and link ${TARGET_NAME} as a shared library" OFF)

if (REEF_BUILD_SHARED_LIBRARY)
    set(BUILD_TYPE SHARED)
else()
    set(BUILD_TYPE STATIC)
endif()

reef_add_library(${TARGET_NAME} ${BUILD_TYPE})

# The source location of the public headers
set(PUBLIC_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include/${TARGET_NAME})
set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(GENERATED_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/include/${TARGET_NAME})

###############################################################################
# Reef::Core module
###############################################################################

set(CORE_PUBLIC_HEADERS
    ${PUBLIC_INCLUDE_DIR}/Core/BaseClass.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Entity.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Event.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/FrameTime.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Material.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Shader.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Mesh.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Shader.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Object.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Scene.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/SceneManager.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/SubclassOf.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Texture.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/Transform.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/TypeInfo.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/UserData.hpp
    ${PUBLIC_INCLUDE_DIR}/Core/View.hpp)

set(CORE_PRIVATE_HEADERS
    ${SRC_DIR}/Core/EntityImpl.hpp
    ${SRC_DIR}/Core/EventImpl.hpp
    ${SRC_DIR}/Core/MaterialImpl.hpp
    ${SRC_DIR}/Core/MeshImpl.hpp
    ${SRC_DIR}/Core/SceneImpl.hpp
    ${SRC_DIR}/Core/SceneObserver.hpp
    ${SRC_DIR}/Core/SceneRenderer.hpp
    ${SRC_DIR}/Core/SceneManagerImpl.hpp
    ${SRC_DIR}/Core/TextureImpl.hpp)

set(CORE_SOURCES
    ${SRC_DIR}/Core/EntityImpl.cpp
    ${SRC_DIR}/Core/EventImpl.cpp
    ${SRC_DIR}/Core/MaterialImpl.cpp
    ${SRC_DIR}/Core/MeshImpl.cpp
    ${SRC_DIR}/Core/Object.cpp
    ${SRC_DIR}/Core/SceneImpl.cpp
    ${SRC_DIR}/Core/SceneRenderer.cpp
    ${SRC_DIR}/Core/SceneManagerImpl.cpp
    ${SRC_DIR}/Core/TextureImpl.cpp
    ${SRC_DIR}/Core/Transform.cpp
    ${SRC_DIR}/Core/TypeInfo.cpp)

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET  public_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES     ${CORE_PUBLIC_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    FILE_SET  private_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES     ${CORE_PRIVATE_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    ${CORE_SOURCES})

###############################################################################
# Reef::Component module
###############################################################################

set(COMPONENT_PUBLIC_HEADERS
    ${PUBLIC_INCLUDE_DIR}/Component/CameraComponent.hpp
    ${PUBLIC_INCLUDE_DIR}/Component/Component.hpp
    ${PUBLIC_INCLUDE_DIR}/Component/MeshComponent.hpp
    ${PUBLIC_INCLUDE_DIR}/Component/ScriptableComponent.hpp)

set(COMPONENT_PRIVATE_HEADERS
    ${SRC_DIR}/Component/ComponentStorage.hpp)

set(COMPONENT_SOURCES
    ${SRC_DIR}/Component/CameraComponent.cpp
    ${SRC_DIR}/Component/Component.cpp
    ${SRC_DIR}/Component/MeshComponent.cpp
    ${SRC_DIR}/Component/ScriptableComponent.cpp
    ${SRC_DIR}/Component/ComponentStorage.cpp)

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET  public_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES     ${COMPONENT_PUBLIC_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    FILE_SET  private_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES     ${COMPONENT_PRIVATE_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    ${COMPONENT_SOURCES})

###############################################################################
# Reef::Platform module
###############################################################################

set(PLATFORM_PUBLIC_HEADERS
    ${PUBLIC_INCLUDE_DIR}/Platform/Application.hpp
    ${PUBLIC_INCLUDE_DIR}/Platform/Input.hpp
    ${PUBLIC_INCLUDE_DIR}/Platform/CommandLineArguments.hpp
    ${PUBLIC_INCLUDE_DIR}/Platform/EntryPoint.hpp
    ${PUBLIC_INCLUDE_DIR}/Platform/Window.hpp
    ${PUBLIC_INCLUDE_DIR}/Platform/WindowManager.hpp)

set(PLATFORM_PRIVATE_HEADERS
    ${SRC_DIR}/Platform/ApplicationImpl.hpp
    ${SRC_DIR}/Platform/WindowManagerImpl.hpp
    ${SRC_DIR}/Platform/WindowImpl.hpp
    ${SRC_DIR}/Platform/Win32/WindowImpl_Win32.hpp)

set(PLATFORM_SOURCES
    ${SRC_DIR}/Platform/ApplicationImpl.cpp
    ${SRC_DIR}/Platform/CommandLineArguments.cpp
    ${SRC_DIR}/Platform/Win32/WindowImpl_Win32.cpp
    ${SRC_DIR}/Platform/WindowManagerImpl.cpp)
    
target_sources(${TARGET_NAME} PUBLIC
    FILE_SET  public_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/include
    FILES     ${PLATFORM_PUBLIC_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    FILE_SET  private_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src
    FILES     ${PLATFORM_PRIVATE_HEADERS})

target_sources(${TARGET_NAME} PRIVATE
    ${PLATFORM_SOURCES})

###############################################################################
# Link with dependencies
###############################################################################

target_link_libraries(${TARGET_NAME} PUBLIC
    Util
    glm::glm 
PRIVATE
    tinygltf
    stduuid
    Rendering)

###############################################################################
# Configure the target
###############################################################################

target_compile_definitions(${TARGET_NAME} PUBLIC GLM_ENABLE_EXPERIMENTAL)

coral_configure_target(${TARGET_NAME})

###############################################################################
# Organize files in the IDE
###############################################################################

source_group("include/Platform" FILES ${PLATFORM_PUBLIC_HEADERS})
source_group("src/Platform"     FILES ${PLATFORM_PRIVATE_HEADERS} ${PLATFORM_SOURCES})

source_group("include/Core" FILES ${CORE_PUBLIC_HEADERS})
source_group("src/Core"     FILES ${CORE_PRIVATE_HEADERS} ${CORE_SOURCES})

source_group("include/Component" FILES ${COMPONENT_PUBLIC_HEADERS})
source_group("src/Component"     FILES ${COMPONENT_PRIVATE_HEADERS} ${COMPONENT_SOURCES})
