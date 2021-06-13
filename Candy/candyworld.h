#ifndef CANDYWORLD_H
#define CANDYWORLD_H
#include<QtCore>

class CandyWorld
{
public:
    QVector<QVector<int>> *world;
    CandyWorld(int w_count, int h_count);
    void Update(int direction);
private:
    int h_count,w_count;
    void Roll();
    QPoint *playerPosition;
    QPoint *candyPosition;
};

#endif // CANDYWORLD_H
