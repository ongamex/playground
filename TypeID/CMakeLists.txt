cmake_minimum_required(VERSION 3.10)

if(WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

add_library(TypeID STATIC typeid.h typeid.cpp)

add_library(slib STATIC slib.h slib.cpp)

add_library(dlib SHARED dlib.cpp typeid.h typeid.cpp)
set_target_properties(dlib PROPERTIES CXX_VISIBILITY_PRESET hidden)

add_executable(Exe ExeMain.cpp PluginInterface.h)
target_link_libraries(Exe TypeID slib)
target_link_libraries(Exe ${CMAKE_DL_LIBS})

add_dependencies(Exe dlib)