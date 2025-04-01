cmake_minimum_required(VERSION 3.16)
project(FallingSandCellularAutomata)

set(CMAKE_CXX_STANDARD 23)

if (WIN32)
    set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2/cmake")
    set(SDL2_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/SDL2/include")
    set(SDL2_LIBRARIES "${CMAKE_SOURCE_DIR}/SDL2/lib/X64/SDL2.lib")
endif()

find_package(SDL2 REQUIRED)
find_package(TBB CONFIG REQUIRED)

# Include SDL2 and project header directories
include_directories(FallingSandCellularAutomata ${SDL2_INCLUDE_DIR})
include_directories("${CMAKE_SOURCE_DIR}/include")

# Add source files
set(SOURCES
        src/world/Chunk.cpp
        src/world/ChunkWorker.cpp
        src/materials/solid/Concrete.cpp
        src/Element.cpp
        src/materials/gas/Fire.cpp
        src/materials/gas/Gas.cpp
        src/world/Grid.cpp
        src/materials/liquid/Liquid.cpp
        src/FallingSand.cpp
        src/utils/Renderer.cpp
        src/materials/solid/Sand.cpp
        src/materials/gas/Smoke.cpp
        src/materials/solid/Solid.cpp
        src/materials/gas/Steam.cpp
        src/utils/ToolHandler.cpp
        src/materials/liquid/Water.cpp
        src/materials/solid/Wood.cpp
        # Add additional .cpp files here
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} TBB::tbb)