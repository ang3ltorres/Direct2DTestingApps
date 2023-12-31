################################
# Global
################################
cmake_minimum_required(VERSION 3.27)
project(Direct2DTestingApps LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_compile_options(-Wall -pedantic)
link_libraries(windowscodecs d2d1 kernel32 user32 gdi32)
add_compile_definitions(UNICODE)
if (CMAKE_COMPILER_IS_GNUCXX)
	add_link_options(-municode)
	add_compile_options(-Wextra)
endif()

function(add_exe TARGET_NAME)
	file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}/src/*.cpp")
	add_executable(${TARGET_NAME} WIN32 ${SOURCES})
	target_include_directories(${TARGET_NAME} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${TARGET_NAME}/include")
endfunction()

################################
# Executables
################################
add_exe(01_window)
add_exe(02_d2d)
add_exe(03_loop_improved)
add_exe(04_bouncing_ball)
add_exe(05_game_structure)
add_exe(06_sprite)
add_exe(07_pong)
