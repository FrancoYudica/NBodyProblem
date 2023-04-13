file(GLOB WOLF_SANDBOX_H *.h)
file(GLOB WOLF_SANDBOX_CPP *.cpp)

add_library(lib_sandbox STATIC
    ${WOLF_SANDBOX_H}
    ${WOLF_SANDBOX_CPP}
)

target_link_libraries(lib_sandbox PRIVATE vendor)
target_link_libraries(lib_sandbox PRIVATE wolf_engine)
