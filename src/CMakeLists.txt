cmake_minimum_required(VERSION 3.0)
project(SmartClock)

add_compile_options(-Wdeprecated-declarations)

find_package(PkgConfig REQUIRED)
find_package(CURL REQUIRED) 
pkg_check_modules(Mosquitto REQUIRED IMPORTED_TARGET libmosquitto )
pkg_check_modules(GTK gtk+-3.0)
include_directories(${GTK_INCLUDE_DIRS} ../inc ../json/include ${CURL_INCLUDE_DIR} /usr/include/gtk-3.0 /usr/include)
link_directories(${GTK_LIBRARY_DIRS})
link_libraries(${GTK_LIBRARIES} ${CURL_LIBRARIES} pthread PkgConfig::Mosquitto)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_executable(${PROJECT_NAME} 
    BottomRow.cpp 
    CurlThread.cpp 
    ForecastDayWidget.cpp 
    ForecastParser.cpp
    LabelWidget.cpp 
    mosquittopp.cpp
    MqttThread.cpp
    SmartClock.cpp 
    TimeUtils.cpp
    TopRow.cpp 
)

add_custom_command(TARGET SmartClock POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/images/ $<TARGET_FILE_DIR:SmartClock>/images)


