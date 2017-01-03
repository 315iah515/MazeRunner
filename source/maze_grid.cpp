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
#include <new>
#include "maze_grid.hpp"


//--------------------------------------------------------------------------------------------------
//  Member Function:
//      MazeGrid()
//
//  Summary:
//      Canonical constructor.
//
//   Parameters:
//      vRows -
//          [in] The number rows that the maze grid will have.
//      vColumns -
//          [in] The number of columns that the grid will contain.
//
//--------------------------------------------------------------------------------------------------
//
MazeGrid::MazeGrid(uint16_t vRows, uint16_t vColumns)
    : mRows(vRows),
      mColumns(vColumns),
      mData(boost::extents[vRows][vColumns]),
      mMt(std::random_device()()),
      mDist(0, vColumns)

{

}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      ~MazeGrid()
//
//  Summary:
//      Maze Grid destructor.
//
//
//
//--------------------------------------------------------------------------------------------------
//
MazeGrid::~MazeGrid()
{
    Clear();
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      ConstructCells()
//
//  Summary:
//      Fills the maze grid with the number of cells equal to the number of rows times the
//      number of columns.
//
//  Returns:
//      Returns true if enough memory can be allocated for all cells or false otherwise.
//
//  Remarks:
//
//--------------------------------------------------------------------------------------------------
//
bool
MazeGrid::ConstructCells()
{
    bool result = true;

    try
    {
        qDebug("Constructing maze cells...");
        for (std::uint16_t i = 0; i < mRows; ++i)
        {
            for(std::uint16_t j = 0; j < mColumns; ++j)
            {
                mData[i][j] = new QGraphicsCellWidget(i, j);

            }
        }

    }
    catch (std::bad_alloc& excep)
    {
        std::cerr << "bad_alloc caught: " << excep.what() << '\n';
        result = false;
    }


    //ConfigureCellNeighbors();

    return result;
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      ClearAndConstructNewDiem()
//
//  Summary:
//      Clears the internal state of the grid before constructing another set of cells.
//
//  Parameters:
//      vRows -
//          [in] The number rows that the maze grid will have.
//      vColumns -
//          [in] The number of columns that the grid will contain.
//
//  Returns:
//      Returns true if enough memory can be allocated for all cells or false otherwise.
//
//--------------------------------------------------------------------------------------------------
//
bool
MazeGrid::ClearAndConstructNewDiem(uint16_t vRows, uint16_t vColumns)
{
    Clear();
    mRows = vRows;
    mColumns = vColumns;
    return ConstructCells();
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      RetrieveCell()
//
//  Summary:
//      .
//
//  Parameters:
//      vRow -
//          [in] The specific row of a cell
//      vColumn -
//          [in] The specific column of a desired cell.
//
//  Returns:
//      Returns an immutable pointer to a cellwidget
//
//--------------------------------------------------------------------------------------------------
//
MazeGrid::CellPtr
MazeGrid::RetrieveCell(uint16_t vRow, uint16_t vColumn)
{
    return mData[vRow][vColumn];
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      RandomCell()
//
//  Summary:
//      .
//
//
//  Returns:
//      Returns an immutable pointer to a random cellwidget contained within the maze
//
//  Remarks:
//      The matrix comprising the grid will not always be a square matrix therefore the row will
//       need to have its own distribution
//
//--------------------------------------------------------------------------------------------------
//
MazeGrid::CellPtr
MazeGrid::RandomCell()
{
    int vRow = mDist(mMt);
    int vColumn = mDist(mMt);

    return mData[vRow][vColumn];
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      Clear()
//
//  Summary:
//      Deallocates the cell widegts from the matrix.
//
//
//--------------------------------------------------------------------------------------------------
//
void
MazeGrid::Clear()
{
    qDebug("Clearing maze cells!");
    for (std::uint16_t i = 0; i < mRows; ++i)
    {
        for(std::uint16_t j = 0; j < mColumns; ++j)
        {
            delete mData[i][j];
        }
    }
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      ConfigureCellNeighbors()
//
//  Summary:
//      Assigns each cell’s neighbor, the four adjoining cells.
//
//  Remarks:
//     Opens all passage ways between cells, all cells have links except for edges.
//
//--------------------------------------------------------------------------------------------------
//
void
MazeGrid::ConfigureCellNeighbors()
{
    qDebug("Configuring cells neighbors...");
    for (std::uint16_t row = 0; row < mRows; ++row)
    {
        for(std::uint16_t column = 0; column < mColumns; ++column)
        {
            CellPtr vPtr = mData[row][column];

            if ( row > 0)
            {
                vPtr->AssignNeighbor(mData[row - 1][column], CellLabel::NORTH);
            }

            if (row < mRows - 1)
            {
                vPtr->AssignNeighbor(mData[row + 1][column], CellLabel::SOUTH);
            }

            if (column > 0)
            {
                vPtr->AssignNeighbor(mData[row][column - 1], CellLabel::WEST);
            }

            if (column < mColumns - 1)
            {
                vPtr->AssignNeighbor(mData[row][column + 1], CellLabel::EAST);
            }
        }
    }

}
