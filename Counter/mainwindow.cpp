#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFrame>
#include <QGridLayout>
#include <QPushButton>
#include <plusbutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , couter(0)
{
    QPushButton *plusButton = new QPushButton(this);
    plusButton->setText("Прибавить");
    QPushButton *minusButton = new QPushButton(this);
    minusButton->setText("Убавить");
    LCDcouter = new QLCDNumber(this);

    QGridLayout *buttonGrid = new QGridLayout(this);
    buttonGrid->addWidget(plusButton,0,0);
    buttonGrid->addWidget(minusButton,0,1);
    buttonGrid->addWidget(LCDcouter,1,0,1,2);


    connect(plusButton,&QPushButton::clicked,this,&MainWindow::plusSlot);
    connect(minusButton,&QPushButton::clicked,this,&MainWindow::minusSlot);

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

