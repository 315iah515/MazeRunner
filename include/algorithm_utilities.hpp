//==================================================================================================
//  File Name:
//      algorithm_utilities.hpp
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
#ifndef ALGORITHM_UTILITIES_HPP_DEFINED
#define ALGORITHM_UTILITIES_HPP_DEFINED

#include "mz_includes.h"


//--------------------------------------------------------------------------------------------------
//  Function Template:
//      SelectRandomly()
//
//  Summary:
//      Does...
//
//  Template Parameters:
//      TP1 -
//          Abc...
//      TP2 -
//          Xyz...
//
//  Parameters:
//      FP1 -
//          [in, out] Abc...
//      FP2 -
//          [in, out] Xyz...
//
//  Returns:
//      {Optional...}
//
//  Remarks:
//      {Optional...}
//
//--------------------------------------------------------------------------------------------------
//
template<typename Iter, typename RandomGenerator>
Iter
SelectRandomly(Iter vStart, Iter vEnd, RandomGenerator& vGenerator)
{
    std::uniform_int_distribution<> vDistrb(0, std::distance(vStart, vEnd) - 1);
    std::advance(vStart, vDistrb(vGenerator));
    return vStart;
}

//--------------------------------------------------------------------------------------------------
//  Function Template:
//      SelectRandomly()
//
//  Summary:
//      Does...
//
//  Template Parameters:
//      TP1 -
//          Abc...
//      TP2 -
//          Xyz...
//
//  Parameters:
//      FP1 -
//          [in, out] Abc...
//      FP2 -
//          [in, out] Xyz...
//
//  Returns:
//      {Optional...}
//
//  Remarks:
//      {Optional...}
//
//--------------------------------------------------------------------------------------------------
//
template<typename Iter>
Iter
SelectRandomly(Iter vStart, Iter vEnd)
{
    static std::random_device vRndm;
    static std::mt19937 vGenerator(vRndm());
    return SelectRandomly(vStart, vEnd, vGenerator);
}

#endif //- ALGORITHM_UTILITIES_HPP_DEFINED
