set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
find_package(Boost REQUIRED)

add_executable(studysync_client
        src/main.cpp
        src/MainWindow.cpp
        src/ClientNetworkManager.cpp
        include/MainWindow.h
        include/ClientNetworkManager.h
)

target_link_libraries(studysync_client PRIVATE
        Qt6::Widgets
        studysync_shared
)

target_include_directories(studysync_client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(studysync_client PRIVATE ${Boost_INCLUDE_DIRS})