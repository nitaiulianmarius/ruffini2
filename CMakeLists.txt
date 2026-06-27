cmake_minimum_required(VERSION 3.21)
project(Ruffini2 LANGUAGES CXX)

find_package(SFML 2.5 COMPONENTS graphics window audio system REQUIRED)

add_executable(Ruffini2
    src/main.cpp
    src/animation.cpp
    src/button.cpp
    src/enemy.cpp
    src/menu_state.cpp
    src/pause_state.cpp
    src/player.cpp
    src/play_state.cpp)
target_compile_features(Ruffini2 PRIVATE cxx_std_17)
target_compile_definitions(Ruffini2 PRIVATE NOMINMAX)
target_include_directories(Ruffini2 PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/header")
target_link_libraries(Ruffini2 PRIVATE sfml-graphics sfml-window sfml-audio sfml-system)

if(MSVC)
    target_compile_options(Ruffini2 PRIVATE /W4)
else()
    target_compile_options(Ruffini2 PRIVATE -Wall -Wextra)
    target_link_options(Ruffini2 PRIVATE -static -static-libstdc++ -static-libgcc)
    get_filename_component(MINGW_RUNTIME_DIR "${CMAKE_CXX_COMPILER}" DIRECTORY)
    set(MINGW_RUNTIME_DLLS
        "${MINGW_RUNTIME_DIR}/libgcc_s_seh-1.dll"
        "${MINGW_RUNTIME_DIR}/libstdc++-6.dll"
        "${MINGW_RUNTIME_DIR}/libwinpthread-1.dll")
endif()

set_target_properties(Ruffini2 PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
foreach(config Debug Release RelWithDebInfo MinSizeRel)
    string(TOUPPER "${config}" config_upper)
    set_target_properties(Ruffini2 PROPERTIES "RUNTIME_OUTPUT_DIRECTORY_${config_upper}" "${CMAKE_BINARY_DIR}/bin")
endforeach()

add_custom_command(TARGET Ruffini2 POST_BUILD
    COMMAND "${CMAKE_COMMAND}" -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:Ruffini2>/data"
    COMMAND_EXPAND_LISTS
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        $<TARGET_RUNTIME_DLLS:Ruffini2> "$<TARGET_FILE_DIR:Ruffini2>"
    COMMAND "${CMAKE_COMMAND}" -E copy_if_different
        ${MINGW_RUNTIME_DLLS} "$<TARGET_FILE_DIR:Ruffini2>"
    VERBATIM)

install(TARGETS Ruffini2 RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_BINARY_DIR}/bin/" DESTINATION bin
    FILES_MATCHING PATTERN "*.dll")
install(DIRECTORY data DESTINATION bin)
