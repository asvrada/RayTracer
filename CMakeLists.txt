cmake_minimum_required(VERSION 3.6)
project(RayTracing)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(PROJ_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

set(INCLUDES_PROJ ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(INCLUDES_SYSTEM /usr/local/include/)
set(INCLUDES_GLM /usr/local/Cellar/glm/0.9.7.4/include/)
set(LIBS /usr/local/lib/)

include_directories(${INCLUDES_SYSTEM} ${INCLUDES_GLM})
link_directories(${LIBS})

set(SOURCE_FILES ${INCLUDES_PROJ} PngWriter.hpp raytracing.cpp include/Color.hpp)
add_executable(RayTracing ${SOURCE_FILES})
target_link_libraries(RayTracing png)