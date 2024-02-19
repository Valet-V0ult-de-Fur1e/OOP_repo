add_library(queue queue.cpp queue.hpp)
target_link_libraries(queue complex)
set_property(TARGET queue PROPERTY CXX_STANDARD 20 )
target_include_directories(queue PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
    $<INSTALL_INTERFACE:include>
)
install(TARGETS queue)