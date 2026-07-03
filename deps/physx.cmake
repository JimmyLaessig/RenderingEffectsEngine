include(FetchContent)

FetchContent_Declare(
  physx
  GIT_REPOSITORY https://github.com/NVIDIA-Omniverse/PhysX.git
  GIT_TAG 107.0-physx-5.6.0)

# Use this file as a key to check if PhysX has already been built
file(SHA256 ${CMAKE_CURRENT_LIST_DIR}/physx.cmake  PHYSX_HASH)

set(PHYSX_SOURCE_DIR ${FETCHCONTENT_BASE_DIR}/physx-src/physx)
set(PHYSX_BUILD_DIR ${PHYSX_SOURCE_DIR}/compiler/vc17win64-cpu-only)
set(PHYSX_INSTALL_DIR ${FETCHCONTENT_BASE_DIR}/physx-install/${PHYSX_HASH})

# Fetch and build PhysX only if it has not been built yet
if (NOT EXISTS ${PHYSX_INSTALL_DIR})

  FETCHContent_MakeAvailable(physx)

  execute_process(COMMAND "${PHYSX_SOURCE_DIR}/generate_projects.bat" vc17win64-cpu-only 
    COMMAND_ERROR_IS_FATAL ANY)

  execute_process(COMMAND ${CMAKE_COMMAND} 
    --build ${PHYSX_BUILD_DIR} 
    --config Release
    COMMAND_ERROR_IS_FATAL ANY)

  execute_process(COMMAND ${CMAKE_COMMAND} 
    --install ${PHYSX_BUILD_DIR} 
    --config Release
    --prefix ${PHYSX_INSTALL_DIR}
    COMMAND_ERROR_IS_FATAL ANY)
  
endif()

add_library(PhysX SHARED IMPORTED GLOBAL)
set_property(TARGET PhysX PROPERTY IMPORTED_LOCATION ${PHYSX_INSTALL_DIR}/bin/win.x86_64.vc143.mt/release/PhysX_64.lib)
set_property(TARGET PhysX PROPERTY IMPORTED_IMPLIB ${PHYSX_INSTALL_DIR}/bin/win.x86_64.vc143.mt/release/PhysX_64.dll)
set_property(TARGET PhysX PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${PHYSX_INSTALL_DIR}/include)
