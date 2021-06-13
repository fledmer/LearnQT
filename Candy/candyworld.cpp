#include "candyworld.h"
#include <random>
#include <time.h>

CandyWorld::CandyWorld(int w_count, int h_count)
{
    this->w_count = w_count;
    this->h_count = h_count;
    srand(time(0));
    playerPosition = new QPoint(1,1);
    candyPosition = new QPoint(1,0);
    world = new QVector<QVector<int>>();
    for(int x = 0; x < h_count; x++)
        world->push_back(QVector<int>(w_count));
    (*world)[1][1] = 1; //Player
    (*world)[0][1] = 2; //Candy
    qDebug() << *world;
}

void CandyWorld::Update(int direction)
{
    (*world)[playerPosition->y()][playerPosition->x()] = 0;
    (*world)[candyPosition->y()][candyPosition->x()] = 0;
    if(direction == 0 & playerPosition->x() != 0)
        playerPosition->setX(playerPosition->x()-1);
    if(direction == 1 & playerPosition->x() != w_count-1)
        playerPosition->setX(playerPosition->x()+1);
    if(direction == 2 & playerPosition->y() != 0)
        playerPosition->setY(playerPosition->y()-1);
    if(direction == 3 & playerPosition->y() != h_count-1)
        playerPosition->setY(playerPosition->y()+1);

    while(*playerPosition == *candyPosition)
    {
        candyPosition->setX(rand()%w_count);
        candyPosition->setY(rand()%h_count);
        qDebug() << "get";
    }
    qDebug() << "PLAYER: " << *playerPosition;
    qDebug() << "CANDY: " << *candyPosition;
    (*world)[playerPosition->y()][playerPosition->x()] = 1;
    (*world)[candyPosition->y()][candyPosition->x()] = 2;
}
