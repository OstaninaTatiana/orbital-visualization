add_library(orbits orbits.cpp include/orbits/orbits.hpp)
set_property(TARGET orbits PROPERTY CXX_STANDARD 20)
target_include_directories(orbits PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
install(TARGETS orbits)