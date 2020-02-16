set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")

add_library(TypeID STATIC typeid.h typeid.cpp)

add_library(slib STATIC slib.h slib.cpp)
add_library(dlib SHARED dlib.cpp typeid.h typeid.cpp)

add_executable(Exe ExeMain.cpp PluginInterface.h)
target_link_libraries(Exe TypeID slib)