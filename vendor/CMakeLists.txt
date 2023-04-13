
message("VENDOR-CMAKE Loading vendor libraries")

add_subdirectory(glad)
add_subdirectory(imgui)
add_subdirectory(glm)

add_library(vendor INTERFACE)

target_link_libraries(vendor INTERFACE glfw)
target_link_libraries(vendor INTERFACE glm)
target_link_libraries(vendor INTERFACE glad)
target_link_libraries(vendor INTERFACE imgui)
