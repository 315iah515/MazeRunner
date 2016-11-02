//==================================================================================================
//  File Name:
//      qgraphics_cellwidget.hpp
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
#ifndef QGRAPGICS_CELLWIDGET_HPP_DEFINED
#define QGRAPGICS_CELLWIDGET_HPP_DEFINED

#include "mz_includes.h"

#include <QGraphicsWidget>

enum class CellLabel
{
    UNKNOWN = 0,
    NORTH,
    SOUTH,
    EAST,
    WEST
};

//--------------------------------------------------------------------------------------------------
//  Class:
//      QGraphicsCellWidget
//
//  Summary:
//      Does ...
//
//
//  Remarks:
//      {Optional...}
//
//  See Also:
//      {Optional...}
//--------------------------------------------------------------------------------------------------
//
class QGraphicsCellWidget : public QGraphicsWidget
{
     Q_OBJECT
     Q_PROPERTY(QColor color READ fillColor WRITE setFillColor)

public:

    using NeighborList = std::vector<QGraphicsCellWidget*>;

    QGraphicsCellWidget(unsigned int row, unsigned int column);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    QColor fillColor() const;
    unsigned int Row() const;
    unsigned int Column() const;
    bool IsLinkedCell(QGraphicsCellWidget* const vpCell) const;


    void AssignNeighbor(QGraphicsCellWidget* vpCell, CellLabel vLabel);

    void setFillColor(QColor color);
    void LinkCell(QGraphicsCellWidget* vpCell, CellLabel vLabel, bool IsBidirectional = true);
    void UnLinkCell(QGraphicsCellWidget* vpCell, CellLabel vLabel, bool IsBidirectional = true);

    NeighborList Neighbors();


private:
    using AdjacentCells = std::vector<QGraphicsCellWidget*>;
    using AdjacentCellLables = std::vector<CellLabel>;
    unsigned int       mRow;
    unsigned int       mColumn;
    QColor             mFillColor;
    AdjacentCells      mLinked;
    AdjacentCellLables mReachableCells;

    CellLabel DetermineReverseDrc(CellLabel vLabel);

};

QColor inline
QGraphicsCellWidget::fillColor() const
{
    return mFillColor;
}

unsigned int inline
QGraphicsCellWidget::Row() const
{
    return mRow;
}

unsigned int inline
QGraphicsCellWidget::Column() const
{
    return mColumn;
}

void inline
QGraphicsCellWidget::setFillColor(QColor color)
{
    mFillColor = color;
}

void inline
QGraphicsCellWidget::AssignNeighbor(QGraphicsCellWidget* vpCell, CellLabel vLabel)
{
    if (vpCell)
    {
        mLinked.push_back(vpCell);
        mReachableCells.push_back(vLabel);
    }

}

#endif //- QGRAPGICS_CELLWIDGET_HPP_DEFINED
