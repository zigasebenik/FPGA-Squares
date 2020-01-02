cmake_minimum_required(VERSION 3.15)
project(DIGITALNO_NACRTOVANJE LANGUAGES C CXX)

#set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)


add_library(SFMLfunctions SFMLfunctions/src/library.cpp SFMLfunctions/include/library.h)
set_target_properties(SFMLfunctions PROPERTIES LINKER_LANGUAGE C)




set(SFML_DIR "D:/SFML-2.5.1/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/" ${CMAKE_MODULE_PATH})
find_package(SFML 2.5 COMPONENTS  window graphics network audio system REQUIRED)
if(SFML_FOUND)

    add_executable(${PROJECT_NAME} FPGAfunctions/main.c SFMLfunctions/src/library.cpp SFMLfunctions/include/library.h FPGAfunctions/src/drawing.c FPGAfunctions/include/drawing.h FPGAfunctions/src/test.c FPGAfunctions/include/test.h FPGAfunctions/include/font_bmp_raw_32_bitDepth.h)

    target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio sfml-window sfml-system sfml-network m)


endif()
