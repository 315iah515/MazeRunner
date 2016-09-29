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

namespace {

    unsigned int sMargin = 30;
    unsigned int sViewHeight = 400;

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
    QWidget(parent, Qt::FramelessWindowHint),
    mpGraphicsView(nullptr),
    mpScene(nullptr),
    mpExitAct(nullptr),
    mpContainerLayout(nullptr),
    mpTopLevelLayout(nullptr)

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
    return QSize(500, 500);
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

    QGraphicsWidget *vpWidget = new QGraphicsWidget;
    vpWidget->setLayout(mpTopLevelLayout);

    int width = qRound(vpWidget->preferredWidth());
    int height = sViewHeight + (2 * sMargin);
    setMinimumSize(width, height);

    mpScene = new QGraphicsScene(0, 0, 400, 400);
    mpScene->setSceneRect(0, 0, width, height);
    mpScene->setBackgroundBrush(QColor(134, 163, 249));
    mpScene->addItem(vpWidget);

}

