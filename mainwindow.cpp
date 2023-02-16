#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(320,370);
    gameField=new GameField();
    helpField=new HelpField();
    connect(gameField,&GameField::ChangeTextSignal,helpField,&HelpField::ChangeTextSlot);
    gridLayout=new QGridLayout();
    centralWidget=new QWidget();
    gridLayout->addWidget(gameField,0,0);
    gridLayout->addWidget(helpField,1,0);
    centralWidget->setLayout(gridLayout);
    setCentralWidget(centralWidget);
    setStyleSheet("background: rgb(90,100,112);");
}

MainWindow::~MainWindow()
{
}

