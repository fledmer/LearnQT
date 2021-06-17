#ifndef CANDYWORLD_H
#define CANDYWORLD_H
#include<QtCore>

class CandyWorld
{
public:
    QVector<QVector<int>> *world;
    int candyEatCount;
    CandyWorld(int w_count, int h_count);
    ~CandyWorld();
    void Update(int direction);
private:
    QVector<QVector<int>>* GenerateMaze(int height,int width);
    int h_count,w_count;
    void Roll();
    QPoint *playerPosition;
    QPoint *candyPosition;
};

#endif // CANDYWORLD_H
