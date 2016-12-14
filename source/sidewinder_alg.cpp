//==================================================================================================
//  File Name:
//      sidewinder_alg.cpp
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
#include "maze_creation.hpp"
#include "algorithm_utilities.hpp"


//--------------------------------------------------------------------------------------------------
//  Member Function:
//      SideWinder()
//
//  Summary:
//      Default constructor
//
//
//  Remarks:
//      Invoked by the AlgorithmFactory to create instances of MazeCreationBehavior
//
//--------------------------------------------------------------------------------------------------
//
SideWinder::SideWinder()
{}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      Build()
//
//  Summary:
//      Algorithm works on each row of the maze grid linking random runs of adjacent cells and
//      then carves north from a random cell each run. The northern row of the resulting maze
//      will have all cells linked in one open corridor.
//
//
//  Parameters:
//      vGrid -
//          [in, out] Mutable Grid instance
//
//
//  Remarks:
//
//
//--------------------------------------------------------------------------------------------------
//
void
SideWinder::Build(MazeGrid &vGrid) const
{
    vGrid.ConstructCells();
    size_t vRows = vGrid.Rows();
    size_t vColumns = vGrid.Columns();
    std::vector<MazeGrid::CellPtr> vRowData;

    std::default_random_engine vDre;
    std::uniform_int_distribution<int> vDi(0, 1);
    bool vAtEasternBoundry = false;
    bool vAtNorthernBoundry = false;
    int random = 1;

    for (size_t i = 0; i < vRows; ++i)
    {
        for(size_t j = 0; j < vColumns; ++j)
        {
            MazeGrid::CellPtr vPtr =  vGrid.RetrieveCell(i,j);
            vRowData.push_back(vPtr);
            vAtEasternBoundry = (j == vColumns - 1);
            vAtNorthernBoundry = (i == 0);
            random = vDi(vDre);

            bool vCloseOut = vAtEasternBoundry || random == 0;

            if (vCloseOut && !vAtNorthernBoundry)
            {
                auto vItr = SelectRandomly(vRowData.begin(), vRowData.end());
                (*vItr)->LinkCell(vGrid.RetrieveCell(i - 1, j), CellLabel::NORTH);
                vRowData.clear();
            }
            else if (!vAtEasternBoundry)
            {
                vPtr->LinkCell(vGrid.RetrieveCell(i, j + 1), CellLabel::EAST);
            }
        }

        vRowData.clear();

    }

}
