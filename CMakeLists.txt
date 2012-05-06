cmake_minimum_required(VERSION 2.6)
project(GAMEARCH)

# INCLUDE MY CUSTOM HELPER STUFF
INCLUDE(Custom_CMake_Utils.cmake)

# Set location to output binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GAMEARCH_SOURCE_DIR}/bin)
set(CMAKE_INCLUDE_PATH "${GAMEARCH_SOURCE_DIR}/include")

include_directories("${GAMEARCH_SOURCE_DIR}/include")

# ADD GLEW AND SFML OR GLFW STUFF HERE OR DEEPER

# These next two are pretty much the same
#set(CMAKE_CXX_FLAGS "-g -std=c++0x")
#add_definitions("-g -std=c++0x")
add_definitions("-g -std=c++0x -DGLEW_STATIC -static")
#add_subdirectory(src)

IF(WIN32)
    set(SFMLDIR "C:/MinGW/")
ENDIF()
find_package(SFML 2 REQUIRED system window graphics network audio)

find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_PATH})

## ADD AN EXECUTABLE TO BUILD
## FORMAT :
##   SET(PROGRAM_NAMES <executable_name>)
##   INSERT_INTO_MAP(<executable_name> <source_file_1> <source_file_2> ... )
set(PROGRAM_NAMES "final")
##set(final "src/final.cpp" "src/model/model.cpp" "src/emitter/emitter.cpp")
set(final "src/final.cpp" 
          "src/model/model.cpp"
          "src/utils/utils.cpp"
          "src/emitter/emitter.cpp"
          "src/emitter/particle.cpp"
          "src/emitter/controller_functions.cpp"
    )
INSERT_INTO_MAP("final" "${final}")

#SET(_VERBOSE TRUE)

foreach(CURRENT_PROGRAM ${PROGRAM_NAMES})
    GET_FROM_MAP("${CURRENT_PROGRAM}" CURRENT_SOURCES)
    message(${CURRENT_SOURCES})
    IF(DEFINED _VERBOSE AND _VERBOSE)
        message("\nBUILDING ${CURRENT_PROGRAM} FROM SOURCES :")
        foreach(SOURCE_FILENAME ${CURRENT_SOURCES})
            message("\t${SOURCE_FILENAME}")
        endforeach(SOURCE_FILENAME)
        message(" ")
    ENDIF(DEFINED _VERBOSE AND _VERBOSE)
    
    add_executable(${CURRENT_PROGRAM} WIN32 MACOSX_BUNDLE ${CURRENT_SOURCES})

    # Detect and add SFML
    target_link_libraries(${CURRENT_PROGRAM} ${SFML_LIBRARIES})

    target_link_libraries(${CURRENT_PROGRAM} ${GLEW_LIBRARY})

    IF(WIN32)
        target_link_libraries(${CURRENT_PROGRAM} opengl32)
    ELSE()
        find_package(OpenGL REQUIRED)
        include_directories(${OPENGL_INCLUDE_DIR})
        TARGET_LINK_LIBRARIES(${program} ${OPENGL_LIBRARIES})
    ENDIF()
endforeach(CURRENT_PROGRAM)

