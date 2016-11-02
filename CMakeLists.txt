cmake_minimum_required (VERSION 2.8.12)

project(MazeRunner)

find_package(Qt5Widgets)
find_package(Boost)

set (CMAKE_CXX_STANDARD 14)

set (MyProjectLib_src ${PROJECT_SOURCE_DIR}/source/mainwindow.cpp
	                  ${PROJECT_SOURCE_DIR}/source/qgraphics_cellwidget.cpp
	                  )

set (MyProjectLib_hdr ${PROJECT_SOURCE_DIR}/include/mainwindow.hpp
	                  ${PROJECT_SOURCE_DIR}/include/qgraphics_cellwidget.hpp)
	                  

#set (MyProjectLib_ui  ${PROJECT_SOURCE_DIR}/forms/main_window.ui)

set (MyProjectBin_src ${PROJECT_SOURCE_DIR}/source/main.cpp
                      ${PROJECT_SOURCE_DIR}/source/maze_grid.cpp
                      ${PROJECT_SOURCE_DIR}/source/maze_creation.cpp
                      ${PROJECT_SOURCE_DIR}/source/binary_tree_alg.cpp)

qt5_wrap_cpp (MyProjectLib_hdr_moc ${MyProjectLib_hdr})
#qt5_wrap_ui (MyProjectLib_ui_moc  ${MyProjectLib_ui})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories (${PROJECT_BINARY_DIR})

add_library (MyProjectLib STATIC
    ${MyProjectLib_src}
    ${MyProjectLib_hdr_moc})

 #${MyProjectLib_ui_moc}

target_link_libraries (MyProjectLib Qt5::Widgets)

add_executable(MazeRunner ${MyProjectBin_src})
qt5_use_modules(MazeRunner Core Gui Widgets)
target_link_libraries (MazeRunner MyProjectLib)
#
# run with cmake -G "Visual Studio 14 2015 Win64" -DCMAKE_BUILD_TYPE=Debug  -DCMAKE_PREFIX_PATH=C:/DevTools/Qt/5.7/msvc2015_64/lib/cmake



