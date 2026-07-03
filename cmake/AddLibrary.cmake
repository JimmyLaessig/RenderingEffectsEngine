
function(reef_add_library TARGET_NAME BUILD_TYPE)

add_library(${TARGET_NAME} ${BUILD_TYPE})

string(TOUPPER "${TARGET_NAME}" TARGET_NAME_UPPERCASE)

# The GenerateExportHeader module contains the function definition for 
# generate_export_header()
include(GenerateExportHeader)

set(GENERATED_HEADER_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated/include/Reef/${TARGET_NAME})

set(EXPORT_HEADER "${GENERATED_HEADER_DIR}/Export.hpp")

# The generate_export_header function is used to generate a file containing
# suitable preprocessor for the EXPORT macros to be used in library classes.
# The header is automatically populated with the proper preprocessor defines
# based on the platform and build type (shared, static). 
# (https://cmake.org/cmake/help/latest/module/GenerateExportHeader.html)
generate_export_header(${TARGET_NAME}
    EXPORT_FILE_NAME ${EXPORT_HEADER}
    EXPORT_MACRO_NAME ${TARGET_NAME_UPPERCASE}_API)

if (${BUILD_TYPE} STREQUAL "STATIC")
    target_compile_definitions(${TARGET_NAME} PUBLIC "${TARGET_NAME_UPPERCASE}_STATIC_DEFINE")
endif()

target_sources(${TARGET_NAME} PUBLIC
    FILE_SET  public_headers
    TYPE      HEADERS
    BASE_DIRS ${CMAKE_CURRENT_BINARY_DIR}/generated/include
    FILES     ${EXPORT_HEADER})

endfunction()
