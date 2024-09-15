cmake_minimum_required(VERSION 3.6)
project(chess-game)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

#=====================================================
# TODO: Change directory QT for windows/mac/linux
# Uncomment correct directory, and comment other directories
#=====================================================

#=====================================================
# Linux (tested in classroom):
#=====================================================
# For other linux variants locate local installation directory Qt5.
# For example on ubuntu search for installation directory using
# >> dpkg --listfiles qtbase5-dev
# Then find path which contains "lib" and "cmake" and "Qt5Core"
#=====================================================
# set(Qt5Core_DIR "/usr/lib/x86_64-linux-gnu/cmake/Qt5Core")
# set(Qt5Widgets_DIR "/usr/lib/x86_64-linux-gnu/cmake/Qt5Widgets")
# set(Qt5Gui_DIR "/usr/lib/x86_64-linux-gnu/cmake/Qt5Gui")

#=====================================================
# Mac
#=====================================================
# set(Qt5Core_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Core")
# set(Qt5Widgets_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Widgets")
# set(Qt5Gui_DIR "~/Qt/5.9.2/clang_64/lib/cmake/Qt5Gui")

#=====================================================
# Windows
#=====================================================
set(QT_VERSION 5)
set(REQUIRED_LIBS_QUALIFIED Qt5::Core Qt5::Gui Qt5::Widgets)

# Check for architecture and set correct Qt version for macOS on ARM64
if (${CMAKE_SYSTEM_PROCESSOR} MATCHES "arm64" AND ${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(CMAKE_PREFIX_PATH "~/Qt/6.2.2/macos/lib/cmake")
    set(QT_VERSION 6)
    set(REQUIRED_LIBS_QUALIFIED Qt6::Core Qt6::Gui Qt6::Widgets)
endif()

set(QT_BUILD Qt${QT_VERSION})
set(REQUIRED_LIBS Core Gui Widgets)

set(CMAKE_CXX_STANDARD 11)

# Source files are restructured according to the new folder structure
set(SOURCE_FILES 
    src/main.cpp 
    src/gui/mainwindow.cpp 
    src/gui/mainwindow.h 
    src/board/chessboard.cpp 
    src/board/chessboard.h 
    src/game/game.cpp 
    src/game/game.h 
    src/pieces/chesspiece.cpp 
    src/pieces/chesspiece.h 
    src/resources.h
)

# Add the executable target
add_executable(chess-game ${SOURCE_FILES})

# Find and link the necessary Qt libraries
find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
target_link_libraries(chess-game ${REQUIRED_LIBS_QUALIFIED})
