#ifndef PLUSBUTTON_H
#define PLUSBUTTON_H
#include <QObject>
#include <QPushButton>

class PlusButton:QPushButton
{
public:
    PlusButton(QObject *parent = 0);

signals:
    void addSignal();
};

#endif // PLUSBUTTON_H
