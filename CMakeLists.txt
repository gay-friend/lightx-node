cmake_minimum_required(VERSION 3.5) # cmake最低版本要求
set(PROJECT_NAME node) #设置工程环境变量
project(${PROJECT_NAME} VERSION 0.1) # 设置工程名称

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# find qt
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(ROOT ${PROJECT_SOURCE_DIR})
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/../lightx-thirdparty)
IF (CMAKE_SYSTEM_NAME MATCHES "Linux")
	MESSAGE(STATUS "current platform: Linux ")
    set(BUILD_DIR ${ROOT}/../build/linux/lib)
    set(LIB_NODE ${ROOT}/../build/linux/libnode.so)
    file(GLOB_RECURSE LIBS ${THIRD_PARTY_DIR}/libs/linux/*so*)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "Windows")
	MESSAGE(STATUS "current platform: Windows")
    set(BUILD_DIR ${ROOT}/../build/win/lib)
    set(LIB_NODE ${ROOT}/../build/linux/node.dll)
    file(GLOB_RECURSE LIBS LIBS ${THIRD_PARTY_DIR}/libs/win/*lib)
ELSEIF (CMAKE_SYSTEM_NAME MATCHES "FreeBSD")
	MESSAGE(STATUS "current platform: FreeBSD")
ELSE ()
    MESSAGE(STATUS "other platform: ${CMAKE_SYSTEM_NAME}")
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件
include_directories(LIBS ${THIRD_PARTY_DIR}/include)

file(GLOB_RECURSE THIRD_PARTY_INCLUDES ${THIRD_PARTY_DIR}/include/*.h*)
# foreach(file ${THIRD_PARTY_INCLUDES})
#     message(${file})
# endforeach()

file(GLOB_RECURSE INCLUDES ${ROOT}/include/*.h*)
# foreach(file ${INCLUDES})
#     message(${file})
# endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件
include_directories(LIBS ${THIRD_PARTY_DIR}/include)
add_subdirectory(src)