//==================================================================================================
//  File Name:
//      maze_creation.hpp
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
#ifndef MAZE_CREATION_HPP_DEFINED
#define MAZE_GREATION_HPP_DEFINED

#include "mz_includes.h"
#include "maze_grid.hpp"


enum class CreationAlgorithm
{
    ALDOUS_BRODER = 0,
    BINARY_TREE,
    ELLER,
    GROWING_TREE,
    HUNT_AND_KILL,
    KRUSKALS,
    SIMPLIIFED_PRIMS,
    TRUE_PRIMS,
    RECURSIVE_BACKTRACKER,
    RECURSIVE_DIVISON,
    SIDEWINDER,
    WILSONS
};


//--------------------------------------------------------------------------------------------------
//  Class:
//      MazeCreationBehavior
//
//  Summary:
//      Base class for all strategies used to create the different maze configurations.
//
//
//  Remarks:
//      {Optional...}
//
//--------------------------------------------------------------------------------------------------
//
class MazeCreationBehavior
{
    public:
        virtual void Build(MazeGrid& vGrid) const = 0;
};


using CreationAlgorithmPtr =  std::unique_ptr<MazeCreationBehavior>;


CreationAlgorithmPtr
AlgorithmFactory(CreationAlgorithm vType);

//--------------------------------------------------------------------------------------------------
//  Class:
//      SideWinder
//
//  Summary:
//     Creates a maze by randomly creating passages to the north, west and east of each cell.
//
//
//  Remarks:
//
//
//--------------------------------------------------------------------------------------------------
//
class SideWinder : public MazeCreationBehavior
{
public:
    void Build(MazeGrid& vGrid) const;

private:
    friend CreationAlgorithmPtr AlgorithmFactory(CreationAlgorithm vType);
    SideWinder();


};

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


#endif //- MAZE_CREATION_HPP_DEFINED
