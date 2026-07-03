file(
   DOWNLOAD
   https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.42.1/get_cpm.cmake
   ${CMAKE_BINARY_DIR}/cmake/get_cpm.cmake
   EXPECTED_HASH SHA256=799143bb9c1fbd14dc9a513eaff03ee1a709c6ee16f32456b50443d66dd7affa
)

include(${CMAKE_BINARY_DIR}/cmake/get_cpm.cmake)

include(tinygltf.cmake)

include(imgui_club.cmake)
include(coral.cmake)
include(stduuid.cmake)