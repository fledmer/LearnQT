#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <candyworld.h>
#include <QGridLayout>
#include <QPalette>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    game = new CandyWorld(10,10);
    world = game->world;
    graphics = new QVector<QVector<QWidget*>>();
    w_count = 10;
    h_count = 10;
    double x_size = 800/w_count;
    double y_size = 800/h_count;
    for(int y = 0; y < h_count; y++)
    {
        graphics->push_back(QVector<QWidget*>());
        for(int x = 0; x < w_count; x++)
        {
            ((*graphics)[y]).push_back(new QWidget(this));
            ((*graphics)[y])[x]->setGeometry(x_size * x,y_size*y,x_size,y_size);
            ((*graphics)[y])[x]->show();
        }
    }


    playerPalette = new QPalette();
    candyPalette = new QPalette();
    voidPalette = new QPalette();
    pxm = QPixmap(":/resource/player.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    playerPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/candy.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    candyPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/world.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    voidPalette->setBrush(QPalette::Window,pxm);
    this->setPalette(*voidPalette);
    ReDraw();

}

void MainWindow::ReDraw()
{
    for(int y = 0; y < h_count; y++)
    {
        for(int x = 0; x < w_count; x++)
        {
            if((*world)[y][x] == 1)
            {
                ((*graphics)[y])[x]->setPalette(*playerPalette);
                ((*graphics)[y])[x]->setAutoFillBackground(true);
                ((*graphics)[y])[x]->show();
            }
            else if((*world)[y][x] == 2)
            {
                ((*graphics)[y])[x]->setPalette(*candyPalette);
                ((*graphics)[y])[x]->setAutoFillBackground(true);
                ((*graphics)[y])[x]->show();
            }
            else
            {
                ((*graphics)[y])[x]->setPalette(*voidPalette);
                //((*graphics)[y])[x]->setPalette(palette());
                ((*graphics)[y])[x]->setAutoFillBackground(true);
                ((*graphics)[y])[x]->show();
            }
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        game->Update(0);
    else if(event->key() == Qt::Key_Right)
        game->Update(1);
    else if(event->key() == Qt::Key_Up)
        game->Update(2);
    else if(event->key() == Qt::Key_Down)
        game->Update(3);
    ReDraw();
}

MainWindow::~MainWindow()
{
    delete ui;
}
