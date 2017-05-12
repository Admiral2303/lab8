# cmake_minimum_required(VERSION 2.8.9)
# project (json)

# # add_executable(proj main.c)

# # adds ./include to compiler include directories
# include_directories(include usr/local/include)

# # uncomment to use libxml2 XML headers
# # include_directories(/usr/include/libxml2)

# # compiles code files from ./src folder
# file(GLOB SOURCES "src/*.cpp")
# # set(PROJECT_LINK_LIBS profecionals progbase xml2 jansson check)
# # to build static lib
# # add_library(mycsv STATIC ${SOURCES})
# add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${SOURCES})
# target_link_libraries(${CMAKE_PROJECT_NAME} jansson progbase-cpp progbase ssl)
# SET(CMAKE_CXX_FLAGS "-std=c++11 -g")




cmake_minimum_required(VERSION 2.8.7)

include_directories(include)
file(GLOB LIB_SOURCES "src/*.cpp")

project (https_server)
add_executable(${CMAKE_PROJECT_NAME} "main.cpp" ${LIB_SOURCES})
target_link_libraries(${CMAKE_PROJECT_NAME} progbase-cpp progbase ssl jansson)

SET(CMAKE_CXX_FLAGS "-std=c++11 -Werror -Wall")
