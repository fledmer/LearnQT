#include "playwindow.h"
#include "ui_playwindow.h"

PlayWindow::PlayWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PlayWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ловушка Ильи");
    this->setGeometry(0,0,1200,800);

    w_size = 3;h_size =3;candyLvl=0;
    StartGame();
    Update();
}

PlayWindow::~PlayWindow()
{
    delete ui;
}

void PlayWindow::StartGame()
{
    if(candyLvl != 0){
    delete candyEatLabel;
    delete candyLvlLabel;
    delete candyWorld;
    delete graphicsMatrix;
    delete playerPalette;
    delete candyPalette;
    delete voidPalette;
    delete wallPalette;
    }

    candyWorld = new CandyWorld(w_size,h_size);
    worldMatrix = candyWorld->world;
    int _w_size = w_size*2+1;
    int _h_size = h_size*2+1;
    //такие размеры нужны для работы с матрицей
    graphicsMatrix = new QVector<QVector<QWidget*>>();
    float widgetSize = fmin(800/_w_size,
                            800/_h_size);

    for(int y = 0; y < _h_size; y++){
        graphicsMatrix->push_back(QVector<QWidget*>());
        for(int x = 0; x < _w_size; x++){
            ((*graphicsMatrix)[y]).push_back(new QWidget(this));
            ((*graphicsMatrix)[y])[x]->setGeometry
                    (widgetSize * x,widgetSize*y,widgetSize,widgetSize);
            ((*graphicsMatrix)[y])[x]->show();
        }
    }

    candyLvlLabel = new QLabel(this);
    candyLvlLabel->setFont(QFont("Caveat",20,20,true));
    candyLvlLabel->setGeometry(820,15,400,100);
    candyLvlLabel->setText("Уровень: " + QString::number(candyLvl));
    candyLvlLabel->show();
    candyEatLabel = new QLabel(this);
    candyEatLabel->setFont(QFont("Caveat",20,20,true));
    candyEatLabel->setGeometry(820,60,400,100);
    candyEatLabel->show();

    QPixmap pxm;
    playerPalette = new QPalette();
    candyPalette = new QPalette();
    voidPalette = new QPalette();
    wallPalette = new QPalette();
    pxm = QPixmap(":/resurces/image/player.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    playerPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resurces/image/candy.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    candyPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resurces/image/world.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    voidPalette->setBrush(QPalette::Window,pxm);
    pxm = QPixmap(":/resurces/image/wall.png");
    pxm = pxm.scaled(((*graphicsMatrix)[0])[0]->size(),Qt::KeepAspectRatioByExpanding);
    wallPalette->setBrush(QPalette::Window,pxm);

    Update();
}

void PlayWindow::keyPressEvent(QKeyEvent *event)
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

void PlayWindow::Update()
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
                ((*graphicsMatrix)[y])[x]->setAutoFillBackground(true);
                ((*graphicsMatrix)[y])[x]->show();
            }
        }
    }

    candyEatLabel->setText("Свинья съела "
    + QString::number(candyWorld->candyEatCount)
    + " конфет");

    if(candyWorld->candyEatCount == 5)
    {
        candyLvl++;w_size+=2;h_size+=2;
        StartGame();
    }
}

