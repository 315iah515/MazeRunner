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



MazeGrid::MazeGrid(uint16_t vRows, uint16_t vColumns)
    : mRows(vRows),
      mColumns(vColumns),
      mData(boost::extents[vRows][vColumns])
{

}
