cmake_minimum_required(VERSION 3.21)
project(RTI)

set(CMAKE_EXE_LINKER_FLAGS "-static")

set(CMAKE_CXX_STANDARD 20)


add_executable(RTI main.cpp
        app/src/Application.cpp
        app/include/Application.hpp
        app/include/Tri.hpp
        app/src/Vector3.cpp
        app/include/Vector3.hpp
        app/include/Math.hpp
        app/include/Camera.hpp
        app/include/Settings.hpp
        app/include/ObjLoader.hpp
        app/include/Timer.hpp
        app/include/Ray.hpp app/include/Hit.hpp
        app/src/Tri.cpp
        app/include/AABB.hpp
        app/src/AABB.cpp
        app/include/BVHNode.hpp)

## add subdirectories
include_directories(${CMAKE_SOURCE_DIR}/app/include)

# add submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/tinyobj)
target_link_libraries(${PROJECT_NAME} PRIVATE tinyobjloader)

# add submodule
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/glm)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)
