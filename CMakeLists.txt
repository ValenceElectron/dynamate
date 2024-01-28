cmake_minimum_required(VERSION 3.28.1)
project(Dynamate)
set(CMAKE_CXX_STANDARD 17)

add_executable(Dynamate src/main.cpp
                src/Draw.cpp
                src/Draw.hpp
                src/render/DrawableObjectManager.cpp
                src/render/DrawableObjectManager.hpp
                src/render/ResourceManager.cpp
                src/render/ResourceManager.hpp
                src/render/UserInterfaceManager.cpp
                src/render/UserInterfaceManager.hpp
                src/render/objects/DrawableObject.cpp
                src/render/objects/DrawableObject.hpp
                src/render/objects/UserInterfaceElement.cpp
                src/render/objects/UserInterfaceElement.hpp
                src/utils/Camera.cpp
                src/utils/Camera.hpp
                src/utils/Loader.cpp
                src/utils/Loader.hpp
                src/utils/ObjectLoader.cpp
                src/utils/ObjectLoader.hpp
                src/utils/ObjectLoader.hpp
                src/utils/OGLSetup.cpp
                src/utils/OGLSetup.hpp
                src/utils/UserInterfaceLoader.cpp
                src/utils/UserInterfaceLoader.hpp)

find_package(glm REQUIRED)
target_link_libraries(Dynamate glm)

find_package(glfw3 3.3 REQUIRED)
target_link_libraries(Dynamate glfw)

find_package(GLEW REQUIRED)
target_link_libraries(Dynamate ${GLEW_LIBRARIES})

find_package(OpenGL REQUIRED)
target_link_libraries(Dynamate OpenGL::GL OpenGL::GLU)


