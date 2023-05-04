
add_subdirectory(Opengl)
add_library(platform_lib INTERFACE)
target_link_libraries(platform_lib INTERFACE opengl_lib)