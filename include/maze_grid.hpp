//==================================================================================================
//  File Name:
//      maze_grid.hpp
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
#ifndef MAZE_GRID_HPP_DEFINED
#define MAZE_GRID_HPP_DEFINED

#include "mz_includes.h"
#include "qgraphics_cellwidget.hpp"

//--------------------------------------------------------------------------------------------------
//  Class:
//      MazeGrid
//
//  Summary:
//      Manages the cells that make up the maze
//
//
//  Remarks:
//      {Optional...}
//
//  See Also:
//      {Optional...}
//--------------------------------------------------------------------------------------------------
//
class MazeGrid
{
public:
    MazeGrid(std::uint16_t vRows, std::uint16_t vColumns);

private:

    using CellPtr = QGraphicsCellWidget*;
    using ArrayType =  boost::multi_array<CellPtr, 2>;
    using Index = ArrayType::index;

    ArrayType     mData;
    std::uint16_t mRows;
    std::uint16_t mColumns;

    void Clear();
};

#endif //- MAZE_GRID_HPP_DEFINED
