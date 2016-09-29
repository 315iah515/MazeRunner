//==================================================================================================
//  File Name:
//      qgraphics_cellwidget.hpp
//
//  Product:
//      MazeRunner
//
//  Interface Header:
//
//
//  Authors:
//      Ian Heaton
//
//  Copyright Notice:
//
//==================================================================================================
//
#ifndef QGRAPGICS_CELLWIDGET_HPP_DEFINED
#define QGRAPGICS_CELLWIDGET_HPP_DEFINED

#include <vector>
#include <functional>

#include <QGraphicsWidget>

enum class CellLabel
{
    NORTH = 0,
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

    using NeighborList = std::vector<std::reference_wrapper<QGraphicsCellWidget>>;


    QGraphicsCellWidget(unsigned int row, unsigned int column);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) Q_DECL_OVERRIDE;

    QColor fillColor() const;
    unsigned int Row() const;
    unsigned int Column() const;

    void setFillColor(QColor color);
    QGraphicsCellWidget& LinkCell(QGraphicsCellWidget& vCell, bool IsBidirectional = true);
    QGraphicsCellWidget& UnLinkCell(QGraphicsCellWidget& vCell, bool IsBidirectional = true);

    NeighborList Neighbors();


private:
    using AdjacentCells = std::vector<QGraphicsCellWidget>;
    unsigned int       mRow;
    unsigned int       mColumn;
    QColor mFillColor;
    AdjacentCells      mLinked;
    CellLabel          mLabel;



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


#endif //- QGRAPGICS_CELLWIDGET_HPP_DEFINED
