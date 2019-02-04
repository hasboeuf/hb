cmake_minimum_required(VERSION 3.5)

project(HbSample)

find_package(Qt5 REQUIRED Core Widgets Network NetworkAuth Xml)
find_package(Hb REQUIRED 2.0.0 HbTools HbLog HbAuth HbPlugin HbNetwork)

add_executable(HbSample "main.cpp")

target_link_libraries(HbSample Qt5::Core Qt5::Widgets Qt5::Network Qt5::Xml HbTools HbLog HbAuth HbPlugin HbNetwork)

install(TARGETS HbSample DESTINATION bin)
