# CMake entry point
cmake_minimum_required (VERSION 2.6)
project (Statek)

set (CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()



# Compile external dependencies 
add_subdirectory (external)

# On Visual 2005 and above, this module can set the debug working directory
cmake_policy(SET CMP0026 OLD)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/external/rpavlik-cmake-modules-fe2273")
#include(CreateLaunchers)
#include(MSVCMultipleProcessCompile) # /MP

if(INCLUDE_DISTRIB)
	add_subdirectory(distrib)
endif(INCLUDE_DISTRIB)

set(CMAKE_EXE_LINKER_FLAGS -static)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(
		external/AntTweakBar-1.16/include/
		external/glfw-3.1.2/include/GLFW/
		external/glm-0.9.7.1/
		external/glew-1.13.0/include/
		external/assimp-3.0.1270/include/
		external/bullet-2.81-rev2613/src/
		external/
		statek/
		.
)

set(ALL_LIBS
		${OPENGL_LIBRARY}
		BulletDynamics
		BulletCollision
		LinearMath
		BulletSoftBody
		glfw
		GLEW_1130
)

add_definitions(
	-DTW_STATIC
	-DTW_NO_LIB_PRAGMA
	-DTW_NO_DIRECT3D
	-DGLEW_STATIC
	-D_CRT_SECURE_NO_WARNINGS
)

set(PHYSICS_SOURCE
		statek/Physics/PhysicsEngine.cpp
		statek/Physics/PhysicsEngine.h)

set(GRAPHICS_SOURCE
		statek/Graphics/Window.cpp
		statek/Graphics/Window.h
		statek/Graphics/Mesh.cpp
		statek/Graphics/Mesh.h
		statek/Graphics/Renderer.cpp
		statek/Graphics/Renderer.h
		statek/Graphics/OpenGLHeaders.h)
set(GAME_SOURCE
		statek/Game.cpp
		statek/Game.h statek/Game/Camera.cpp statek/Game/Camera.h statek/Game/Interfaces/IRenderable.h statek/Game/Interfaces/Actor.h statek/Game/GameElements/TestObject.cpp statek/Game/GameElements/TestObject.h statek/Game/GameElements/Asteroid.cpp statek/Game/GameElements/Asteroid.h statek/Game/Interfaces/IPhysicsable.h statek/Game/GameElements/PlayerShip.cpp statek/Game/GameElements/PlayerShip.h statek/Game/GameElements/Bullet.cpp statek/Game/GameElements/Bullet.h statek/Game/Interfaces/Actor.cpp statek/Game/Interfaces/IPhysicsable.cpp statek/Game/Interfaces/IRenderable.cpp statek/Game/Interfaces/ITickable.cpp statek/Game/Interfaces/ITickable.h)
# Tutorial 9 - several objects
add_executable(statek
		${GRAPHICS_SOURCE}
		${GAME_SOURCE}
		${PHYSICS_SOURCE}
		statek/tutorial09_several_objects.cpp
)
target_link_libraries(statek
	${ALL_LIBS}
)