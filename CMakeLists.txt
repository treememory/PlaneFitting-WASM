CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(PlaneFitting)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

if (DEFINED EMSCRIPTEN)
add_executable(${PROJECT_NAME} src/PlaneFitting.cpp src/PlaneFitting.h)

	# set(CMAKE_EXECUTABLE_SUFFIX ".wasm")
	set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "-Os")
	set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS    "-Os -s WASM=1 --no-entry -s EXPORTED_FUNCTIONS='[_malloc,_free]' -s EXPORTED_RUNTIME_METHODS='[ccall,cwrap]'")
else()
  add_executable(${PROJECT_NAME}Sample src/test.cpp src/PlaneFitting.cpp)
endif()