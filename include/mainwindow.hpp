//==================================================================================================
//  File Name:
//      mainwindow.hpp
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
#ifndef MAINWINDOW_HPP_DEFINED
#define MAINWINDOW_HPP_DEFINED

#include <QWidget>
#include <vector>


class QAction;
class QGraphicsView;
class QGraphicsScene;
class QGraphicsCellWidget;
class QGraphicsLinearLayout;
class QGraphicsGridLayout;

//--------------------------------------------------------------------------------------------------
//  Class:
//      MainWindow
//
//  Summary:
//      Holds the graphics scene housing Maze
//
//
//  Remarks:
//      {Optional...}
//
//  See Also:
//      {Optional...}
//--------------------------------------------------------------------------------------------------
//
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QSize sizeHint() const Q_DECL_OVERRIDE;

protected:
    void mouseMoveEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
    //void resizeEvent(QResizeEvent *event) Q_DECL_OVERRIDE;

private slots:


private:

    QGraphicsView        *mpGraphicsView;
    QGraphicsScene        *mpScene;
    QAction               *mpExitAct;

    QGraphicsGridLayout   *mpContainerLayout;
    QGraphicsLinearLayout *mpTopLevelLayout;



    QPoint     mDragPosition;

    void CreateActions();
    void CreateSceneLayout();

};

#endif // MAINWINDOW_HPP_DEFINED
