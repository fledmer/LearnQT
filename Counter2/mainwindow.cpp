#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFrame>
#include <QGridLayout>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , couter(0)
{
    QAction *plusAction = new QAction("Plus",this);
    QAction *minusAction = new QAction("Minus",this);
    QAction *exitAction = new QAction("Exit",this);
    LCDcouter = new QLCDNumber(this);

    QMenu *actionMenu;
    actionMenu = menuBar()->addMenu("Action");
    actionMenu->addAction(plusAction);
    actionMenu->addAction(minusAction);
    actionMenu->addSeparator();
    actionMenu->addAction(exitAction);

    QGridLayout *buttonGrid = new QGridLayout(this);
    buttonGrid->addWidget(LCDcouter,0,0);


    connect(plusAction,&QAction::triggered,this,&MainWindow::plusSlot);
    connect(minusAction,&QAction::triggered,this,&MainWindow::minusSlot);
    connect(exitAction,&QAction::triggered,this,&QApplication::quit);

    QWidget* mainWidget = new QWidget;
    mainWidget->setLayout(buttonGrid);
    setCentralWidget(mainWidget);
}

void MainWindow::plusSlot()
{
  couter++;
  LCDcouter->display(couter);
}

void MainWindow::minusSlot()
{
  couter--;
  LCDcouter->display(couter);
}

MainWindow::~MainWindow()
{
    delete ui;
}

