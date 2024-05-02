cmake_minimum_required(VERSION 3.28)
project(SFML_PlayGround)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
endif(CCACHE_FOUND)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(SFML_PlayGround src/main.cpp)
target_link_libraries(SFML_PlayGround PRIVATE sfml-graphics)
target_compile_features(SFML_PlayGround PRIVATE cxx_std_20)

if(WIN32)
    add_custom_command(
        TARGET SFML_PlayGround
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SFML_PlayGround>
        VERBATIM)

    # If we are building in release mode, turn on compiler optimizations and remove debug info & console
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(SFML_PlayGround PROPERTIES LINK_FLAGS_RELEASE "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
        set_target_properties(SFML_PlayGround PROPERTIES COMPILE_OPTIONS "/O2")
    endif ()
endif()

## Copy resources to build directory
#add_custom_command(
#    TARGET SFML_PlayGround
#    COMMENT "Copy shaders if different"
#    POST_BUILD
#    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CMAKE_SOURCE_DIR}/shaders/HexagonalTruchet.frag $<TARGET_FILE_DIR:SFML_PlayGround>/shaders/HexagonalTruchet.frag
#    # Add more lines here for each shader file
#    VERBATIM
#)


install(TARGETS SFML_PlayGround)
# Runtime output directory to be in bin folder
#set_target_properties(SFML_PlayGround PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)