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
//      paint()
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
        painter->setBrush(Qt::black);
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
//      IsLinkedCell()
//
//  Summary:
//      Determines if parameter is connected to cell via a passage. Included in list of
//      neighboring cells.
//
//  Parameters:
//      vpCell -
//          [in, out] Immutable pointer to maze cell
//
//--------------------------------------------------------------------------------------------------
//
bool
QGraphicsCellWidget::IsLinkedCell(QGraphicsCellWidget *const vpCell) const
{
    bool result = false;

    for (auto vp : mLinked)
    {
        if (vp == vpCell)
        {
            result = true;
            break;
        }
    }

    return result;
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
QGraphicsCellWidget::LinkCell(QGraphicsCellWidget *vpCell, CellLabel vLabel, bool IsBidirectional)
{
    if (vpCell != nullptr)
    {
        mLinked.push_back(vpCell);
        mReachableCells.push_back(vLabel);

        if (IsBidirectional)
        {
            vpCell->LinkCell(this, DetermineReverseDrc(vLabel), false);
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
QGraphicsCellWidget::UnLinkCell(QGraphicsCellWidget *vpCell, CellLabel vLabel, bool IsBidirectional)
{
    if (vpCell != nullptr)
    {
        auto vItr = std::find(mLinked.begin(), mLinked.end(), vpCell);
        auto vItr2 = std::find(mReachableCells.begin(), mReachableCells.end(), vLabel);

        if (vItr != mLinked.end() && vItr2 != mReachableCells.end())
        {
            mLinked.erase(vItr);
            mReachableCells.erase(vItr2);

            if (IsBidirectional)
            {
                vpCell->UnLinkCell(this, DetermineReverseDrc(vLabel), false);

            }
        }
    }
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      DetermineReverseDrc()
//
//  Summary:
//      Determines the directional label for the linked cell in relation to this instance.
//      For bidirectional linking and unlinking
//
//
//  Parameters:
//      vLabel -
//          [in] scoped enumeration direction of the adjoining cell, the cell being linked to
//          this instance
//
//  Returns:
//      A CellLabel
//
//--------------------------------------------------------------------------------------------------
//
CellLabel
QGraphicsCellWidget::DetermineReverseDrc(CellLabel vLabel)
{
    CellLabel vResult;

    if (vLabel == CellLabel::NORTH)
    {
        vResult = CellLabel::SOUTH;
    }
    else if (vLabel == CellLabel::EAST)
    {
        vResult = CellLabel::WEST;
    }
    else if (vLabel == CellLabel::SOUTH)
    {
        vResult = CellLabel::NORTH;
    }
    else
    {
        vResult = CellLabel::EAST;
    }

    return vResult;

}
