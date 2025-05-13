cmake_minimum_required(VERSION 3.12)
project(App_SixJoint LANGUAGES CXX)

# ——————————————————————————————————————————————
# 1) Where you installed Bullet3
#————————————————————————————————————————————————
# Change this to your actual install location

set(BULLET_ROOT_DIR "/home/yuth/robotics_dev/bullet3-3.25")
set(BULLET_LIB_DIR "${BULLET_INSTALL_DIR}/lib")
set(BULLET_INC_DIR "${BULLET_INSTALL_DIR}/include")
include_directories(
    ${BULLET_ROOT_DIR}/src
    ${BULLET_ROOT_DIR}/examples
    ${BULLET_ROOT_DIR}/examples/ThirdPartyLibs
    ${BULLET_ROOT_DIR}/examples/ThirdPartyLibs/enet/include
    # ${BULLET_ROOT_DIR}/examples/ThirdPartyLibs/clsocket/src
)

#————————————————————————————————————————————————
# 2) C++ standard and definitions
#————————————————————————————————————————————————
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Bullet example needs these
add_compile_definitions(
    GLEW_INIT_OPENGL11_FUNCTIONS=1
    GLEW_STATIC
    GLEW_DYNAMIC_LOAD_ALL_GLX_FUNCTIONS=1
)

#————————————————————————————————————————————————
# 3) Your sources
#————————————————————————————————————————————————
set(APP_SIXJOINT_SRCS
    MySixJoint.cpp

)

add_executable(App_SixJoint ${APP_SIXJOINT_SRCS})

#————————————————————————————————————————————————
# 4) Include path
#————————————————————————————————————————————————
target_include_directories(App_SixJoint PRIVATE
    ${BULLET_INC_DIR}
)

#————————————————————————————————————————————————
# 5) Find installed Bullet libs
#————————————————————————————————————————————————
# Macro to simplify find_library
macro(find_bullet_lib var name)
    find_library(${var}
        NAMES ${name}
        PATHS ${BULLET_LIB_DIR}
        NO_DEFAULT_PATH
    )
    if(NOT ${var})
        message(FATAL_ERROR "Could not find Bullet library: ${name} in ${BULLET_LIB_DIR}")
    endif()
endmacro()

find_bullet_lib(LIB_SM BulletSharedMemory)
find_bullet_lib(LIB_BEBL BulletExampleBrowserLib)
find_bullet_lib(LIB_FILE_BUL BulletFileLoader)
find_bullet_lib(LIB_WORLDIMP BulletWorldImporter)
find_bullet_lib(LIB_SOFTBODY BulletSoftBody)
find_bullet_lib(LIB_DYNA BulletDynamics)
find_bullet_lib(LIB_COLL BulletCollision)
find_bullet_lib(LIB_IDY_UTILS BulletInverseDynamicsUtils)
find_bullet_lib(LIB_IDY BulletInverseDynamics)
find_bullet_lib(LIB_LMath LinearMath)
find_bullet_lib(LIB_OGW OpenGLWindow)
find_bullet_lib(LIB_GW gwen)
find_bullet_lib(LIB_BIK BussIK)
find_bullet_lib(LIB_B3C Bullet3Common)

#————————————————————————————————————————————————
# 6) Link everything explicitly
#————————————————————————————————————————————————
target_link_libraries(App_SixJoint PRIVATE
    ${LIB_SM}
    ${LIB_BEBL}
    ${LIB_FILE_BUL}
    ${LIB_WORLDIMP}
    ${LIB_SOFTBODY}
    ${LIB_DYNA}
    ${LIB_COLL}
    ${LIB_IDY_UTILS}
    ${LIB_IDY}
    ${LIB_LMath}
    ${LIB_OGW}
    ${LIB_GW}
    ${LIB_BIK}
    ${LIB_B3C}
    pthread
    dl
)

#————————————————————————————————————————————————
# 7) Optional: version & debug postfix
#————————————————————————————————————————————————
set_target_properties(App_SixJoint PROPERTIES
    VERSION 3.25
    DEBUG_POSTFIX _d
)
