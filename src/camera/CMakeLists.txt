set(PROJECT_NAME camera) #设置工程环境变量
project(${PROJECT_NAME} VERSION 0.1) # 设置工程名称

file(GLOB_RECURSE SRC *.h *.cpp)
foreach(file ${SRC})
    message(${file})
endforeach()

add_library(${PROJECT_NAME} SHARED ${SRC} ${THIRD_PARTY_INCLUDES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${THRRD_PARTY_LIB} ${LIB_NODE})
message(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}${BIN_SUFFIX} ${LIB_OUTPUT_DIR}/${PROJECT_NAME}${BIN_SUFFIX}
        )