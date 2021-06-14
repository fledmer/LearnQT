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
    float windowHeight = 900;
    float windowWeight = 1400;
    //Создаем мир
    w_count = 4;
    h_count = 4;
    game = new CandyWorld(w_count,h_count);
    w_count = w_count*2+1;
    h_count = h_count*2+1;
    world = game->world;
    //Создаем игровое графическое поле
    graphics = new QVector<QVector<QWidget*>>();
    float blockSize = fmin(windowHeight/h_count,windowWeight/w_count);
    QWidget *maingraphicsWidget = new QWidget(this);
    maingraphicsWidget->resize(blockSize*w_count,blockSize*h_count);
    this->setGeometry(1920/2-blockSize*1.4*w_count/2,100,blockSize*w_count*1.4,blockSize*h_count*1.4);

    for(int y = 0; y < h_count; y++)
    {
        graphics->push_back(QVector<QWidget*>());
        for(int x = 0; x < w_count; x++)
        {
            ((*graphics)[y]).push_back(new QWidget(maingraphicsWidget));
            ((*graphics)[y])[x]->setGeometry(blockSize * x,blockSize*y,blockSize,blockSize);
            ((*graphics)[y])[x]->show();
        }
    }
    //Создаем текстовое поле для статистики
    candyEatLabel = new QLabel(this);
    candyEatLabel->setText("Свинья съела 0 конфет");
    candyEatLabel->setFont(QFont("Arial",15,1));
    //Добавляем графическое поле в Грид
    QGridLayout *mainGrid = new QGridLayout(this);
    mainGrid->addWidget(maingraphicsWidget,0,0,8,8);
    mainGrid->addWidget(candyEatLabel,0,8,1,2);
    mainGrid->setSpacing(0);
    //Создаем фоны для виджетов
    playerPalette = new QPalette();
    candyPalette = new QPalette();
    voidPalette = new QPalette();
    wallPalette = new QPalette();
    QPixmap pxm;
    pxm = QPixmap(":/resource/player.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    playerPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/candy.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    candyPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/world.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    voidPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/wall.png");
    pxm = pxm.scaled(((*graphics)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    wallPalette->setBrush(QPalette::Window,pxm);
    //this->setPalette(*voidPalette);

    this->ui->centralwidget->setLayout(mainGrid);

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
            else if((*world)[y][x] == -1)
            {
                ((*graphics)[y])[x]->setPalette(*wallPalette);
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
    candyEatLabel->setText("Свинья съела " + QString::number(game->candyEatCount) + " конфет");
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
