add_executable(miniclang)

file(GLOB MC_SRC_FILES
  "*.cpp"
)

file(GLOB MC_HEADER_FILES
  "*.h"
)

target_sources(miniclang
  PUBLIC
  main.cpp
  ${MC_SRC_FILES}
  ${MC_HEADER_FILES}
  )

target_include_directories(
  miniclang PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
