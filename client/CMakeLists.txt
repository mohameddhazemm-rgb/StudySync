set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Boost REQUIRED)

file(GLOB_RECURSE SRC_FILES src/*.cpp)
file(GLOB_RECURSE HEADER_FILES include/*.h)

add_executable(studysync_client
        ${SRC_FILES}
        ${HEADER_FILES}
        resources.qrc
)

target_link_libraries(studysync_client PRIVATE
        Qt6::Widgets
        studysync_shared
)

target_include_directories(studysync_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(studysync_client PRIVATE ${Boost_INCLUDE_DIRS})