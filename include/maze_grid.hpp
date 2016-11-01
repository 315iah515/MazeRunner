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
//      Manages the life time and attributes of the cells that make up the maze.
//      Does not display the cells this is left to the graphics scene within the main window.
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
    using CCellPtr = QGraphicsCellWidget const*;
    using CellPtr   = QGraphicsCellWidget*;

    MazeGrid(std::uint16_t vRows, std::uint16_t vColumns);
    ~MazeGrid();

    bool ConstructCells();
    bool ClearAndConstructNewDiem(std::uint16_t vRows, std::uint16_t vColumns);


    CellPtr      RetrieveCell(std::uint16_t vRow, std::uint16_t vColumn);
    std::uint16_t Rows() const;
    std::uint16_t Columns() const;

private:

    using ArrayType =  boost::multi_array<CellPtr, 2>;
    using Index     = ArrayType::index;

    ArrayType     mData;
    std::uint16_t mRows;
    std::uint16_t mColumns;

    void Clear();
    void ConfigureCellNeighbors();
};


std::uint16_t inline
MazeGrid::Rows() const
{
    return mRows;
}

std::uint16_t inline
MazeGrid::Columns() const
{
    return mColumns;
}

#endif //- MAZE_GRID_HPP_DEFINED
