
message("GLAD-CMAKE Adding GLAD library")


file(GLOB C_FILES glad/*.c)
file(GLOB C_H_FILES glad/*.h)

add_library(
    glad STATIC
    ${C_FILES}
    ${C_H_FILES}
)

target_include_directories(
    glad INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)