

add_subdirectory(Wolf)
add_library(dependencies INTERFACE)
target_link_libraries(dependencies INTERFACE engine_lib)

