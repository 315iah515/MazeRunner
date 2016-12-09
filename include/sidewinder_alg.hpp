//==================================================================================================
//  File Name:
//      sidewinder_alg.hpp
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
#ifndef SIDEWINDER_ALG_HPP_DEFINED
#define SIDEWINDER_ALG_HPP_DEFINED

#include "maze_creation.hpp"


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


#endif //- SIDEWINDER_ALG_HPP_DEFINED
