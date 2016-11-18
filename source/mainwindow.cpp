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
    mpScene(nullptr),
    mpExitAct(nullptr),
    mpContainerLayout(nullptr),
    mpTopLevelLayout(nullptr),
    mGrid(16, 16),
    mpUi(new Ui::MazeWidget),
    mWidth(200),
    mHeight(200)

{
    mpUi->setupUi(this);

    QPalette Palette(palette());
    Palette.setColor(QPalette::Window, QColor(53,53,53));
    Palette.setColor(QPalette::WindowText, Qt::white);
    Palette.setColor(QPalette::Base, QColor(15,15,15));
    Palette.setColor(QPalette::AlternateBase, QColor(53,53,53));
    Palette.setColor(QPalette::ToolTipBase, Qt::white);
    Palette.setColor(QPalette::ToolTipText, Qt::white);
    //Palette.setColor(QPalette::Text, Qt::white);
    Palette.setColor(QPalette::Button, QColor(53,53,53));
    Palette.setColor(QPalette::ButtonText, Qt::white);
    Palette.setColor(QPalette::BrightText, Qt::red);

    Palette.setColor(QPalette::Highlight, QColor(142,45,197).lighter());
    Palette.setColor(QPalette::HighlightedText, Qt::black);
    Palette.setColor(QPalette::Disabled, QPalette::Text, Qt::darkGray);
    Palette.setColor(QPalette::Disabled, QPalette::ButtonText, Qt::darkGray);
    setPalette(Palette);


    CreateActions();

    CreateSceneLayout();

    mpUi->GraphicsView->setRenderHints(QPainter::Antialiasing| QPainter::TextAntialiasing);
    //mpUi->GraphicsView->setBackgroundBrush(Qt::white);
    mpUi->GraphicsView->setScene(mpScene);
    mpUi->GraphicsView->setFrameStyle(0);
    mpUi->GraphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    mpUi->GraphicsView->show();

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
//      QSize instance
//--------------------------------------------------------------------------------------------------
//
QSize
MainWindow::sizeHint() const
{
    return QSize(mWidth, mHeight);
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

    QGraphicsWidget *vpWidget = new QGraphicsWidget;
    vpWidget->setLayout(mpTopLevelLayout);

    int width = qRound(vpWidget->preferredWidth());
    int height = qRound(vpWidget->preferredHeight());

    //- Should set the over all size of the top widget to be rectanglar
    //  with extra padding
    //mpUi->GraphicsView->setMinimumSize(width, height);
    mWidth = width + (40 * 2);
    mHeight = height + 170;
    setMinimumSize(mWidth, mHeight);

    mpScene = new QGraphicsScene(this);
    mpScene->setBackgroundBrush(QColor(134, 163, 249));
    mpScene->addItem(vpWidget);
    mpScene->setSceneRect(0, 0, width, height);

}

