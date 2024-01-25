cmake_minimum_required(VERSION 3.5) # cmake最低版本要求
set(PROJECT_NAME node) #设置工程环境变量
project(${PROJECT_NAME} VERSION 0.1) # 设置工程名称

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# 默认debug编译
IF(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
ENDIF()
# 编译产物标志
IF(CMAKE_BUILD_TYPE MATCHES Debug)
	set(BUILD_FLAG "d")
ELSE()
	set(BUILD_FLAG "")
ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

IF(CMAKE_SYSTEM_NAME MATCHES Linux)
    set(LIB_SUFFIX .so)
    set(BIN_SUFFIX .so)
ELSE()
    set(LIB_SUFFIX .lib)
    set(BIN_SUFFIX .dll)
ENDIF(CMAKE_SYSTEM_NAME MATCHES Linux)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../build/${CMAKE_SYSTEM_NAME}/node)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../build/${CMAKE_SYSTEM_NAME}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/../build/${CMAKE_SYSTEM_NAME}/lib)

set(LIB_OUTPUT_DIR ${PROJECT_SOURCE_DIR}/../build/${CMAKE_SYSTEM_NAME}/bin/${CMAKE_BUILD_TYPE}/lib)
set(LIB_NODE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/node${BUILD_FLAG}${LIB_SUFFIX})
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/../lightx-thirdparty)
file(GLOB_RECURSE THRRD_PARTY_LIB ${THIRD_PARTY_DIR}/lib/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/*${LIB_SUFFIX})
file(GLOB_RECURSE THRRD_PARTY_BIN ${THIRD_PARTY_DIR}/bin/${CMAKE_SYSTEM_NAME}/${CMAKE_BUILD_TYPE}/*${BIN_SUFFIX})
message(Output: ${OUTPUT_DIR})
message(THIRD_PARTY_DIR: ${THIRD_PARTY_DIR})
foreach(file ${THRRD_PARTY_LIB})
    message(${file})
endforeach()
foreach(file ${THRRD_PARTY_BIN})
    message(${file})
endforeach()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(LIGHTX_INCLUD_DIR ${PROJECT_SOURCE_DIR}/../lightx/include)
include_directories(${LIGHTX_INCLUD_DIR})
include_directories(${THIRD_PARTY_DIR}/include)

file(GLOB_RECURSE THIRD_PARTY_INCLUDES ${THIRD_PARTY_DIR}/include/*.h*)
file(GLOB_RECURSE LIGHTX_INCLUDES ${LIGHTX_INCLUD_DIR}/node/*.h* ${LIGHTX_INCLUD_DIR}/utils/*.h*)

add_subdirectory(src)

# file(GLOB_RECURSE TARGETP_LIB ${CMAKE_BINARY_DIR}/bin/${LIB_SUBDIR}/*${BIN_SUFFIX})
# file(COPY ${TARGETP_LIB} DESTINATION ${OUTPUT_DIR}/lib)
# add_executable(main test/main.cpp test/utils.cpp include/utils/utils.h)
# target_link_libraries(main PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${THRRD_PARTY_LIB})
# add_library(testnode SHARED test/testnode.cpp)
# target_link_libraries(testnode PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${THRRD_PARTY_LIB} ${LIB_NODE})
# add_executable(testcv test/testcv.cpp)
# target_link_libraries(testcv PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${THRRD_PARTY_LIB})
