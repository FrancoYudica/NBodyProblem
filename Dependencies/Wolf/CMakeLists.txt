add_subdirectory(vendor)
add_subdirectory(Wolf)
add_subdirectory(Platform)

# Creates the wolf_engine_library
add_library(engine_lib INTERFACE)


# Adds all it's dependecies
#target_link_libraries(wolf_engine_library INTERFACE vendor)
target_link_libraries(engine_lib INTERFACE vendor_lib)
target_link_libraries(engine_lib INTERFACE wolf_engine_lib)
target_link_libraries(engine_lib INTERFACE platform_lib)