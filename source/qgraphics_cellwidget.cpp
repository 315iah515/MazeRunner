//==================================================================================================
//  File Name:
//      qgraphics_cellwidget.cpp
//
//  Product:
//      MazeRunner
//
//  Authors:
//      Ian Heaton
//
//  Copyright Notice:
//
//==================================================================================================
//
#include <QPainter>
#include "qgraphics_cellwidget.hpp"


//--------------------------------------------------------------------------------------------------
//  Member Function:
//      MEMBER_FUNCTION_NAME()
//
//  Summary:
//      Does...
//
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
//  Exceptions:
//      {Optional...}
//
//  Remarks:
//      {Optional...}
//
//  See Also:
//      {Optional...}
//--------------------------------------------------------------------------------------------------
//
void
QGraphicsCellWidget::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    QBrush brush = painter->brush();
    painter->setBrush(mFillColor);
    painter->drawRect(rect());
    painter->setBrush(brush);
}
