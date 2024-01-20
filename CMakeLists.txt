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
    set(LIB_NODE ${ROOT}/../build/win/Debug/node.lib)
    file(GLOB_RECURSE LIBS ${THIRD_PARTY_DIR}/libs/win/*lib)
ENDIF(CMAKE_SYSTEM_NAME MATCHES "Linux")

foreach(file ${LIBS})
    message(${file})
endforeach()

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${BUILD_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})
set(EXECUTABLE_OUTPUT_PATH ${BUILD_DIR})
set(LIBRARY_OUTPUT_PATH ${BUILD_DIR})
set(ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR})

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件
include_directories(${THIRD_PARTY_DIR}/include)

file(GLOB_RECURSE THIRD_PARTY_INCLUDES ${THIRD_PARTY_DIR}/include/*.h*)
# foreach(file ${THIRD_PARTY_INCLUDES})
#     message(${file})
# endforeach()

file(GLOB_RECURSE INCLUDES ${ROOT}/include/*.h*)
# foreach(file ${INCLUDES})
#     message(${file})
# endforeach()

include_directories(${PROJECT_SOURCE_DIR}/include) # 添加头文件
include_directories(${THIRD_PARTY_DIR}/include)
add_subdirectory(src)

add_executable(main test/main.cpp test/utils.cpp include/utils/utils.h)
target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${LIBS})
add_library(testnode SHARED test/testnode.cpp)
target_link_libraries(testnode PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${LIBS} ${LIB_NODE})
