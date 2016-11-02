//==================================================================================================
//  File Name:
//      mainwindow.cpp
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
#include <QtWidgets>

#include <QtDebug>

#include "mainwindow.hpp"
#include "qgraphics_cellwidget.hpp"
#include "maze_creation.hpp"

namespace {

    unsigned int sMargin = 30;
    unsigned int sHeight = 400;
    unsigned int sWidth = 400;

}
//--------------------------------------------------------------------------------------------------
//  Member Function:
//      MainWindow()
//
//  Summary:
//      Canonical Constructor
//
//
//
//--------------------------------------------------------------------------------------------------
//
MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent/*, Qt::FramelessWindowHint*/),
    mpGraphicsView(nullptr),
    mpScene(nullptr),
    mpExitAct(nullptr),
    mpContainerLayout(nullptr),
    mpTopLevelLayout(nullptr),
    mGrid(8, 8)

{

    CreateActions();

    CreateSceneLayout();

    mpGraphicsView = new QGraphicsView(this);
    mpGraphicsView->setRenderHints(QPainter::Antialiasing| QPainter::TextAntialiasing);
    mpGraphicsView->setScene(mpScene);
    mpGraphicsView->setFrameStyle(0);
    mpGraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mpGraphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mpGraphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    mpGraphicsView->show();

}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      ~MainWindow()
//
//  Summary:
//      Destructor
//
//
//
//--------------------------------------------------------------------------------------------------
//
MainWindow::~MainWindow()
{

}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      sizeHint()
//
//  Summary:
//
//
//   Returns:
//      QSize instance set to the minimumu for the clock
//--------------------------------------------------------------------------------------------------
//
QSize
MainWindow::sizeHint() const
{
    return QSize(sWidth, sHeight);
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      mousePressEvent()
//
//  Summary:
//      Grabs the current screen position of left mouse button when depressed.
//
//   Parameters:
//      event -
//          [in, out] Mutable pointer to Mouse event
//--------------------------------------------------------------------------------------------------
//
void
MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        mDragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      mouseMoveEvent()
//
//  Summary:
//      Moves the widget once the left mouse button is pressed to the screen position determined
//      by the the mouse drag.
//
//   Parameters:
//      event -
//          [in, out] Mutable pointer to Mouse event
//--------------------------------------------------------------------------------------------------
//
void
MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - mDragPosition);
        event->accept();
    }
}


//--------------------------------------------------------------------------------------------------
//  Member Function:
//      CreateActions()
//
//  Summary:
//      Creates the QActions that are invoked from the QMenu items within the min window.
//
//
//
//--------------------------------------------------------------------------------------------------
//
void
MainWindow::CreateActions()
{
    mpExitAct = new QAction(tr("E&xit"), this);
    mpExitAct->setShortcut(tr("Ctrl+Q"));
    mpExitAct->setStatusTip(tr("Exit the application"));
    connect(mpExitAct, &QAction::triggered, this, &QWidget::close);
    addAction(mpExitAct);

}

//--------------------------------------------------------------------------------------------------
//  Member Function:
//      CreateSceneLayout()
//
//  Summary:
//      Does...
//
//
//
//  Returns:
//      {Optional...}
//
//  Exceptions:
//      {Optional...}
//
//  Remarks:
//
//
//  See Also:
//      {Optional...}
//--------------------------------------------------------------------------------------------------
//
void
MainWindow::CreateSceneLayout()
{

    mpContainerLayout = new QGraphicsGridLayout;

    mpContainerLayout->setVerticalSpacing(0.0);
    mpContainerLayout->setHorizontalSpacing(0.0);

    CreationAlgorithmPtr CreationPtr = AlgorithmFactory(CreationAlgorithm::BINARY_TREE);
    CreationPtr->Build(mGrid);

    // row , column

    for (int i = 0; i < mGrid.Rows(); ++i)
    {
        for (int j = 0; j < mGrid.Columns(); ++j)
        {
            mpContainerLayout->addItem(mGrid.RetrieveCell(i, j), i, j);
        }
    }

    mpTopLevelLayout = new QGraphicsLinearLayout(Qt::Vertical);
    mpTopLevelLayout->addItem(mpContainerLayout);
    mpTopLevelLayout->setSpacing(sMargin);
    mpTopLevelLayout->setContentsMargins(30, 40, 30, 30);

    QGraphicsWidget *vpWidget = new QGraphicsWidget;
    vpWidget->setLayout(mpTopLevelLayout);

    int width = qRound(vpWidget->preferredWidth());
    int height = qRound(vpWidget->preferredHeight());
    //int height = sViewHeight + (2 * sMargin);
    setMinimumSize(width, height);

    sWidth = width;
    sHeight = height;

    mpScene = new QGraphicsScene(this);
    mpScene->setSceneRect(0, 0, width, height);
    mpScene->setBackgroundBrush(QColor(134, 163, 249));
    mpScene->addItem(vpWidget);

}

