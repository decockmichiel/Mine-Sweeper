include(CMakeSources.txt)

add_library(core
    ${CORE_SOURCES}
    ${CORE_HEADERS}
)

target_include_directories(core PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(core PRIVATE
    Qt6::Quick
)
