set(TARGET_NAME ReefDemoApp)

add_executable(${TARGET_NAME})

set(TARGET_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(TARGET_SOURCES
    ${TARGET_SRC_DIR}/main.cpp
)

target_sources(${TARGET_NAME} PRIVATE 
    ${TARGET_SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE
    Reef)

coral_configure_target(${TARGET_NAME})
