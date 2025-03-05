cmake_minimum_required(VERSION 3.16)
project(FallingSandCellularAutomata)

set(CMAKE_CXX_STANDARD 23)

find_package(SDL2 REQUIRED)

# Include SDL2 and project header directories
include_directories(FallingSandCellularAutomata ${SDL2_INLCUDE_DIRS})
include_directories("${CMAKE_SOURCE_DIR}/include")

# Add source files
set(SOURCES
        src/Chunk.cpp
        src/ChunkWorker.cpp
        src/Concrete.cpp
        src/Element.cpp
        src/Fire.cpp
        src/Gas.cpp
        src/Grid.cpp
        src/Liquid.cpp
        src/PhysicsSim.cpp
        src/Renderer.cpp
        src/Sand.cpp
        src/Smoke.cpp
        src/Solid.cpp
        src/Steam.cpp
        src/ToolHandler.cpp
        src/Water.cpp
        src/Wood.cpp
        # Add additional .cpp files here
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link SDL2 libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})