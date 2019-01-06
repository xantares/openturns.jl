cmake_minimum_required (VERSION 3.0)

if (NOT DEFINED CMAKE_BUILD_TYPE)
  set (CMAKE_BUILD_TYPE Release CACHE STRING "Build type")
endif ()

project (openturns.jl)

find_package (JlCxx REQUIRED)
find_package (OpenTURNS REQUIRED)

add_library (openturns_julia MODULE openturns_julia.cpp)
target_link_libraries (openturns_julia OT ${Julia_LIBRARY} JlCxx::cxxwrap_julia)
set_target_properties (openturns_julia PROPERTIES PREFIX "")

set (JULIA_INSTALL_PATH share/julia/stdlib/v1.0 CACHE PATH "Julia install directory")

install (FILES openturns.jl DESTINATION ${JULIA_INSTALL_PATH})
install (TARGETS openturns_julia DESTINATION ${JULIA_INSTALL_PATH})

enable_testing ()

add_test (NAME trigger_recompile COMMAND ${CMAKE_COMMAND} -E touch_nocreate ${PROJECT_SOURCE_DIR}/openturns.jl)

macro (ot_add_test name)
  add_test (NAME ${name} COMMAND ${Julia_EXECUTABLE} --compile=all ${PROJECT_SOURCE_DIR}/t_${name}.jl)
  set_tests_properties(${name} PROPERTIES ENVIRONMENT "JULIA_LOAD_PATH=${PROJECT_SOURCE_DIR}:;LD_LIBRARY_PATH=${PROJECT_BINARY_DIR}" DEPENDS trigger_recompile)
endmacro ()

ot_add_test (base)
ot_add_test (distribution)
