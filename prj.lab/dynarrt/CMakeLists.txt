add_library(dynarrt INTERFACE dynarrt.hpp)
set_property(TARGET dynarrt PROPERTY CXX_STANDARD 20)
target_include_directories(dynarrt INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/..>
  $<INSTALL_INTERFACE:include>
)