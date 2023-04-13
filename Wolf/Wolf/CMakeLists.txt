message("Adding WolfEngine")

file(GLOB WOLF_CORE_H            core/*.h)
file(GLOB WOLF_CORE_CPP          core/*.cpp)

file(GLOB WOLF_IMGUI_LAYER_H     imgui_layer/*.h)
file(GLOB WOLF_IMGUI_LAYER_CPP   imgui_layer/*.cpp)

file(GLOB WOLF_RENDERING_H       rendering/*.h)
file(GLOB WOLF_RENDERING_CPP     rendering/*.cpp)

add_library(
    wolf_engine STATIC
    ${WOLF_CORE_H}
    ${WOLF_CORE_CPP}
    ${WOLF_IMGUI_LAYER_H}
    ${WOLF_IMGUI_LAYER_CPP}
    ${WOLF_RENDERING_H}
    ${WOLF_RENDERING_CPP}
    )

target_link_libraries(wolf_engine PRIVATE vendor)


target_include_directories(
    wolf_engine INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)