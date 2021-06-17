#include "gamewindow.h"

GameWindow::GameWindow(QWidget *parent)
    : QWidget(parent)
{
    this->setGeometry(0,0,1200,800);
    this->show();
    StartGame();
    Update();
}

GameWindow::~GameWindow()
{

}

void GameWindow::StartGame()
{

    candyWorld = new CandyWorld(w_size,h_size);
    worldMatrix = candyWorld->world;
    int _w_size = w_size*2+1;
    int _h_size = h_size*2+1;
    //такие размеры нужны для работы с матрицей
    graphicsMatrix = new QVector<QVector<QWidget*>>();
    float widgetSize = fmin(this->width()/_w_size,
                            this->height()/_h_size);

    for(int y = 0; y < _h_size; y++){
        graphicsMatrix->push_back(QVector<QWidget*>());
        for(int x = 0; x < _w_size; x++){
            ((*graphicsMatrix)[y]).push_back(new QWidget(this));
            ((*graphicsMatrix)[y])[x]->setGeometry
                    (widgetSize * x,widgetSize*y,widgetSize,widgetSize);
            ((*graphicsMatrix)[y])[x]->show();
        }
    }
    candyEatLabel = new QLabel(this);
    candyEatLabel->setGeometry(0,0,100,100);
    QPixmap pxm;
    pxm = QPixmap(":/resource/player.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    playerPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/candy.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    candyPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/world.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    voidPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resource/wall.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    wallPalette->setBrush(QPalette::Window,pxm);
}

void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Left)
        candyWorld->Update(0);
    else if(event->key() == Qt::Key_Right)
        candyWorld->Update(1);
    else if(event->key() == Qt::Key_Up)
        candyWorld->Update(2);
    else if(event->key() == Qt::Key_Down)
        candyWorld->Update(3);
    Update();
}

void GameWindow::Update()
{
    for(int y = 0; y < h_size*2+1; y++)
    {
        for(int x = 0; x < w_size*2+1; x++)
        {
            if((*worldMatrix)[y][x] == 1)
            {
                ((*graphicsMatrix)[y])[x]->setPalette(*playerPalette);
                ((*graphicsMatrix)[y])[x]->setAutoFillBackground(true);
                ((*graphicsMatrix)[y])[x]->show();
            }
            else if((*worldMatrix)[y][x] == 2)
            {
                ((*graphicsMatrix)[y])[x]->setPalette(*candyPalette);
                ((*graphicsMatrix)[y])[x]->setAutoFillBackground(true);
                ((*graphicsMatrix)[y])[x]->show();
            }
            else if((*worldMatrix)[y][x] == -1)
            {
                ((*graphicsMatrix)[y])[x]->setPalette(*wallPalette);
                ((*graphicsMatrix)[y])[x]->setAutoFillBackground(true);
                ((*graphicsMatrix)[y])[x]->show();
            }
            else
            {
                ((*graphicsMatrix)[y])[x]->setPalette(*voidPalette);
                //((*graphics)[y])[x]->setPalette(palette());
                ((*graphicsMatrix)[y])[x]->setAutoFillBackground(true);
                ((*graphicsMatrix)[y])[x]->show();
            }
        }
    }
    candyEatLabel->setText("Свинья съела "
    + QString::number(candyWorld->candyEatCount)
    + " конфет");
}


