

set(WOLF_ENGINE_RELATIVE_TO_ROOT_PATH "Dependencies/WolfEngine")

add_subdirectory(WolfEngine)
add_library(dependencies INTERFACE)
target_link_libraries(dependencies INTERFACE engine_lib)

include_directories(dependencies "WolfEngine/Wolf")
