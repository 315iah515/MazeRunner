//==================================================================================================
//  File Name:
//      binary_tree_alg.hpp
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
#ifndef BINARY_TREE_ALG_HPP_DEFINED
#define BINARY_TREE_ALG_HPP_DEFINED

//#include "maze_creation.hpp"


//--------------------------------------------------------------------------------------------------
//  Class:
//      BinaryTree
//
//  Summary:
//     Creates a maze by randomly creating passages to the north or east of each cell.
//
//
//  Remarks:
//
//
//--------------------------------------------------------------------------------------------------
//
class BinaryTree : public MazeCreationBehavior
{
public:
    void Build(MazeGrid& vGrid) const;

private:
    friend CreationAlgorithmPtr AlgorithmFactory(CreationAlgorithm vType);
    BinaryTree();

};

#endif //- BINARY_TREE_ALG_HPP_DEFINED
