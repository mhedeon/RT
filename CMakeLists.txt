cmake_minimum_required(VERSION 3.12)
project(RT)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -Wextra")
include_directories(libft frameworks)
link_directories(libft frameworks)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(RT
        src/main.c
        src/vector.c
        src/window.c
        src/intersect.c
        src/normal.c
        src/scene.c
        src/camera.c
        src/object.c
        src/read.c
        src/light.c
        src/init.c
        src/trace.c
        src/trash.c
        src/slice.c)

find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_ttf REQUIRED)

include_directories(${SDL2_INCLUDE_DIR})
#        ${SDL2_IMAGE_INCLUDE_DIR}
#        ${SDL2_TTF_INCLUDE_DIR})
#target_link_libraries(RT -lft ${SDL2_LIBRARY})
target_link_libraries(RT ${SDL2_LIBRARY} )
#        ${SDL2_IMAGE_LIBRARIES}
#        ${SDL2_TTF_LIBRARIES})
target_link_libraries(RT -lft)
#find_package(SDL2)

#if(NOT SDL2_FOUND)
#    set(SDL2_BIN_DIR "${CMAKE_CURRENT_BINARY_DIR}/sdl")
#    include(ExternalProject)
#    ExternalProject_Add(sdlLibrary
#            PREFIX ${SDL2_BIN_DIR}/source
#            INSTALL_DIR ${SDL2_BIN_DIR}
#            CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${SDL2_BIN_DIR}
#            GIT_REPOSITORY "https://github.com/SDL-mirror/SDL"
#            GIT_TAG "release-2.0.9"
#            GIT_PROGRESS ON)
#    add_dependencies(RT sdlLibrary)
#    target_link_libraries(RT PRIVATE ${SDL2_BIN_DIR}/lib/somesortoflib.dylib)
#    target_include_directories(RT PRIVATE ${SDL2_BIN_DIR}/include)
#else()
#    target_link_libraries(RT PRIVATE ${SDL2_LIBRARIES} -lft)
#    target_include_directories(RT PRIVATE ${SDL2_INCLUDE_DIR})
#endif()
