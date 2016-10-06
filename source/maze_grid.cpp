//==================================================================================================
//  File Name:
//      maze_grid.cpp
//
//  Product:
//      MazeRunner
//
//
//  Authors:
//      Ian Heaton
//
//==================================================================================================
//
#include "maze_grid.hpp"


MazeGrid::MazeGrid()
    : mRows(0),
      mColumns(0),
      mpData(nullptr)
{

}


MazeGrid::MazeGrid(uint16_t vRows, uint16_t vColumns)
    : mRows(vRows),
      mColumns(vColumns),
      mpData(new ArrayType(boost::extents[vRows][vColumns]))
{

}
