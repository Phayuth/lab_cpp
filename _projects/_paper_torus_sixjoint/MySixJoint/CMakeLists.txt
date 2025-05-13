# Specify the minimum CMake version
cmake_minimum_required(VERSION 3.10)

# Project name
project(App_SixJoint)

# Set the path to the Bullet3 source code
# Update this path to your Bullet3 source directory
set(BULLET_PHYSICS_SOURCE_DIR "/home/yuth/ws_yuthdev/bullet3-3.25")
# Set the path to the Bullet3 build directory
set(BULLET_PHYSICS_BUILD_DIR "${BULLET_PHYSICS_SOURCE_DIR}/build_cmake")


# Include directories for Bullet3
include_directories(
    ${BULLET_PHYSICS_SOURCE_DIR}/src
    ${BULLET_PHYSICS_SOURCE_DIR}/examples
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/ThirdPartyLibs
)

# Define the source files for your application
set(RobotSimulator_SRCS
    MySixJoint.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/b3RobotSimulatorClientAPI_NoDirect.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/IKTrajectoryHelper.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/TinyRenderer/TinyRenderer.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServer.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsClient.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsDirect.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/SharedMemory/PhysicsServerCommandProcessor.cpp
    ${BULLET_PHYSICS_SOURCE_DIR}/examples/Utils/b3ResourcePath.cpp
)

# Add executable
add_executable(App_SixJoint ${RobotSimulator_SRCS})

# Link Bullet3 shared libraries from the local build directory
target_link_libraries(App_SixJoint
    ${BULLET_PHYSICS_BUILD_DIR}/src/BulletDynamics/libBulletDynamics.so
    ${BULLET_PHYSICS_BUILD_DIR}/src/BulletCollision/libBulletCollision.so
    ${BULLET_PHYSICS_BUILD_DIR}/src/LinearMath/libLinearMath.so
)



# # Add definitions for OpenGL and GLEW
# add_definitions("-DGLEW_STATIC")
# include_directories(${BULLET_PHYSICS_SOURCE_DIR}/btgui/OpenGLWindow/GlewWindows)

# # Link OpenGL and pthread
# find_package(OpenGL REQUIRED)
# target_link_libraries(App_SixJoint
#     ${OPENGL_gl_LIBRARY}
#     pthread
#     dl
# )
