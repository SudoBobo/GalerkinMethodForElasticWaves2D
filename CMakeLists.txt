cmake_minimum_required(VERSION 3.0)
project(GalerkinMethodForElasticWaves2D)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

file(GLOB SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

find_package(Boost COMPONENTS filesystem REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
add_executable(GalerkinMethodForElasticWaves2D ${SOURCE_FILES})
target_link_libraries(GalerkinMethodForElasticWaves2D ${Boost_LIBRARIES})


