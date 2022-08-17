cmake_minimum_required(VERSION 3.22)
project(LoginSnapshot)

set(CMAKE_CXX_STANDARD 23)

add_executable(LoginSnapshot main.cpp utility.h)
target_link_libraries(LoginSnapshot Mf.lib)
target_link_libraries(LoginSnapshot Mfplat.lib)
target_link_libraries(LoginSnapshot mfuuid.lib)

target_link_libraries(LoginSnapshot mf.lib)
target_link_libraries(LoginSnapshot mfplat.lib)
target_link_libraries(LoginSnapshot mfplay.lib)
target_link_libraries(LoginSnapshot mfreadwrite.lib)
target_link_libraries(LoginSnapshot mfuuid.lib)
target_link_libraries(LoginSnapshot wmcodecdspuuid.lib)
