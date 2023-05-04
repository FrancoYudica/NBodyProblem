
message("Adding Platform-Opengl")

file(GLOB WOLF_OPENGL_IMPL_CPP "*.cpp")
file(GLOB WOLF_OPENGL_IMPL_H ".h")

add_library(
    opengl_lib STATIC
    ${WOLF_OPENGL_IMPL_H}
    ${WOLF_OPENGL_IMPL_CPP}
)

target_link_libraries(opengl_lib PRIVATE vendor_lib)
target_link_libraries(opengl_lib PRIVATE wolf_engine_lib)
