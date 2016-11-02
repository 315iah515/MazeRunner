//==================================================================================================
//  File Name:
//      maze_creation.cpp
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
//  Function:
//      AlgorithmFactory()
//
//  Summary:
//      Factory function for creating the different maze creation algorithms.
//
//   Parameters:
//      vType -
//          [in] The number rows that the maze grid will have.
//
//
//   Returns:
//      Mutable pointer to the base type
//
//
//   Remarks:
//     Base classes of the MazeCreationBehavior must declare their constructors private and
//     set this fucntion as a private friend.
//
//--------------------------------------------------------------------------------------------------
//
CreationAlgorithmPtr
AlgorithmFactory(CreationAlgorithm vType)
{
    if (vType == CreationAlgorithm::BINARY_TREE)
    {
        return std::unique_ptr<MazeCreationBehavior>(new BinaryTree);
    }
    else
    {
        return std::unique_ptr<MazeCreationBehavior>(new TestC);
    }

}
