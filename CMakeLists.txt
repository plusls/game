cmake_minimum_required(VERSION 3.7)
project(game)

set(CMAKE_CXX_STANDARD 14)

set(SOURCE_FILES src/main.cpp src/GameControl.cpp src/GameControl.h src/FlyingObject.cpp src/FlyingObject.h src/Textures.cpp src/Textures.h src/Draw.cpp src/Draw.h src/GameEvent.cpp src/GameEvent.h)
add_executable(game ${SOURCE_FILES})

#static
#set(SFML_STATIC_LIBRARIES TRUE)
#set(CMAKE_FIND_LIBRARY_SUFFIXES .a${CMAKE_FIND_LIBRARY_SUFFIXES})


#build_type
set(CMAKE_BUILD_TYPE "DEBUG")
#SET(CMAKE_BUILD_TYPE "RELEASE")

#debug
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g")

#release
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")


if(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    #Set CMake's module path to find the SFML Lib
    #set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "/usr/share/SFML/cmake/Modules/")
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/SFML/cmake/Modules/")
    set(SFML_ROOT "SFML/")


elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    #Set CMake's module path to find the SFML Lib
    SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "C:\\lib\\SFML-2.4.2\\cmake\\Modules")
    SET(CMAKE_PREFIX_PATH ${CMAKE_PREFIX_PATH} "C:\\lib\\SFML-2.4.2")
    SET(SFML_ROOT "C:\\lib\\SFML-2.4.2")


    SET(SFML_STATIC_LIBRARIES ON)
endif()



#Find the SFML lib
find_package(SFML 2 COMPONENTS graphics window network audio system)
#message(${SFML_LIBRARIES})

#查找多线程库
find_package(Threads)
target_link_libraries(game ${CMAKE_THREAD_LIBS_INIT})


if (SFML_FOUND)
    INCLUDE_DIRECTORIES(${SFML_INCLUDE_DIR})
    target_link_libraries(game ${SFML_LIBRARIES})
endif ()

#static
if(SFML_STATIC_LIBRARIES)
    message(${SFML_DEPENDENCIES})
    target_link_libraries(game ${SFML_DEPENDENCIES})
    set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} "-static")
endif()