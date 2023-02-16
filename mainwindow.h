#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "game.h"
#include "helpfield.h"
#include <QMainWindow>
#include <QGridLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    GameField *gameField;
    HelpField *helpField;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
};
#endif // MAINWINDOW_H
