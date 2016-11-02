//==================================================================================================
//  File Name:
//      binary_tree_alg.cpp
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
#include "binary_tree_alg.hpp"


//--------------------------------------------------------------------------------------------------
//  Member Function:
//      BinaryTree()
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
BinaryTree::BinaryTree()
{}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      Build()
//
//  Summary:
//      Builds the Maze and Links adjoining maze cells in either the East or North directions.
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
BinaryTree::Build(MazeGrid &vGrid) const
{
    vGrid.ConstructCells();
    size_t vRows = vGrid.Rows();
    size_t vColumns = vGrid.Columns();

    std::default_random_engine vDre;
    std::uniform_int_distribution<int> vDi(0, 1);

    for (size_t i = 0; i < vRows; ++i)
    {
        for(size_t j = 0; j < vColumns; ++j)
        {
            MazeGrid::CellPtr vPtr =  vGrid.RetrieveCell(i,j);
            int random = vDi(vDre);


            if ( random == 1 && i > 0)
            {
                vPtr->LinkCell(vGrid.RetrieveCell(i - 1, j), CellLabel::NORTH);
            }

            if (random == 0 && j < vColumns - 1)
            {
                vPtr->LinkCell(vGrid.RetrieveCell(i, j + 1), CellLabel::EAST);
            }

        }
    }


}
