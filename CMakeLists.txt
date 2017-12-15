cmake_minimum_required(VERSION 3.9)
project(Finite_Diffs_Diffusion)

set(CMAKE_CXX_STANDARD 14)
#set(Boost_DEBUG ON)
#set(BOOST_ROOT "./boost_1_65_1")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GTK_CFLAGS} -static -static-libgcc -static-libstdc++")

#[[find_package(Boost)
IF (Boost_FOUND)

    message(STATUS "Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost_LIBRARY_DIRS: ${Boost_LIBRARY_DIRS}")
    message(STATUS "Boost_LIBRARIES: ${Boost_LIBRARIES}")
    message(STATUS "Boost_VERSION: ${Boost_VERSION}")

    include_directories(${Boost_INCLUDE_DIRS})
endif()]]


add_executable(Finite_Diffs_Diffusion main.cpp IO.cpp IO.h Calculator.cpp Calculator.h)
target_link_libraries(Finite_Diffs_Diffusion #[[${Boost_LIBRARIES}]])