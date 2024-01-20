set(PROJECT_NAME threshold) #设置工程环境变量
project(${PROJECT_NAME} VERSION 0.1) # 设置工程名称

file(GLOB_RECURSE SRC *.h *.cpp)
foreach(file ${SRC})
    message(${file})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SRC} ${THIRD_PARTY_INCLUDES} ${INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${LIBS} ${LIB_NODE})