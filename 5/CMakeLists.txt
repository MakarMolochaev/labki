cmake_minimum_required(VERSION 3.15)
project(Makar_RT VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -ffast-math")

find_package(OpenMP REQUIRED)

set(SOURCES
    main.cpp
    Vector3.cpp
    Sphere.cpp
    Plane.cpp
    Triangle.cpp
    Scene.cpp
    Color.cpp
    ObjectFactory.cpp
    Material.cpp
    PointLight.cpp
)

add_executable(program ${SOURCES})

target_link_libraries(program OpenMP::OpenMP_CXX)