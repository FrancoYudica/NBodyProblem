
message("GLAD-CMAKE Adding GLAD library")


file(GLOB C_FILES glad/*.c)
file(GLOB C_H_FILES glad/*.h)
file(GLOB KHR_HEADER KHR/*.h)

add_library(
    glad STATIC
    ${C_FILES}
    ${C_H_FILES}
    ${KHR_HEADER}
)

target_include_directories(
    glad INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)