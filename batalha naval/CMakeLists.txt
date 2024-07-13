cmake_minimum_required(VERSION 3.29)
set(CMAKE_C_COMPILER "C:/MinGW/bin/gcc")
set(CMAKE_CXX_COMPILER "C:/MinGW/bin/g++.exe")
project(batalhaNaval)

add_executable(CmakePresets C:/Users/leona/Documents/arquivos_C++/CPE/BatalhaNaval/src/main.cpp)

#add_library(LibTest STATIC IMPORTED)
#set_target_properties(LibTest PROPERTIES
#    IMPORTED_LOCATION C:/Users/leona/Documents/arquivos_C++/CPE/BatalhaNaval/lib/fmt.lib
#    INTERFACE_INCLUDE_DIRECTORIES C:/Users/leona/Documents/arquivos_C++/CPE/BatalhaNaval/include
#)
find_package(raylib CONFIG REQUIRED)
target_link_libraries(CmakePresets PRIVATE raylib)


include_directories(C:/dev/vcpkg/installed/x64-windows/include)



