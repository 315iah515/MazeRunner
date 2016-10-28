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
//      QGraphicsCellWidget()
//
//  Summary:
//      Constructs a maze cell
//
//
//  Parameters:
//      row -
//          [in] The row of the matrix that cell instance resides in
//      column -
//          [in] The column of the matric that the cell instance resides in
//
//
//--------------------------------------------------------------------------------------------------
//
QGraphicsCellWidget::QGraphicsCellWidget(unsigned int row, unsigned int column)
    :mRow(row),
     mColumn(column),
     mFillColor(Qt::white)

{

}

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

    if (mLinked.empty())
    {
        painter->drawRect(rect());
    }
    else if (mLinked.size() == 4)
    {
        painter->setPen(Qt::NoPen);
        painter->drawRect(rect());

    }
    else
    {
        if (std::count(mReachableCells.begin(), mReachableCells.end(), CellLabel::NORTH) == 0)
        {
            painter->drawLine(rect().topLeft(), rect().topRight());
        }

        if (std::count(mReachableCells.begin(), mReachableCells.end(), CellLabel::EAST) == 0)
        {
            painter->drawLine(rect().topRight(), rect().bottomRight());
        }

        if (std::count(mReachableCells.begin(), mReachableCells.end(), CellLabel::SOUTH) == 0)
        {
            painter->drawLine(rect().bottomRight(), rect().bottomLeft());
        }

        if (std::count(mReachableCells.begin(), mReachableCells.end(), CellLabel::WEST) == 0)
        {
            painter->drawLine(rect().bottomLeft(), rect().topLeft());
        }

    }

    painter->setBrush(brush);
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      LinkCell()
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
//--------------------------------------------------------------------------------------------------
//
void
QGraphicsCellWidget::LinkCell(QGraphicsCellWidget *vpCell, bool IsBidirectional)
{
    if (vpCell != nullptr)
    {
        mLinked.push_back(vpCell);
        if (IsBidirectional)
        {
            vpCell->LinkCell(this, false);

        }
    }
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      UnLinkCell()
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
//--------------------------------------------------------------------------------------------------
//
void
QGraphicsCellWidget::UnLinkCell(QGraphicsCellWidget *vpCell, bool IsBidirectional)
{
    if (vpCell != nullptr)
    {
        auto vItr = std::find(mLinked.begin(), mLinked.end(), vpCell);

        if (vItr != mLinked.end())
        {
            mLinked.erase(vItr);

            if (IsBidirectional)
            {
                vpCell->UnLinkCell(this, false);

            }
        }
    }
}
