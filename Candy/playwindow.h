#ifndef PLAYWINDOW_H
#define PLAYWINDOW_H
#include<QtWidgets>
#include <QMainWindow>
#include <candyworld.h>

namespace Ui {
class PlayWindow;
}

class PlayWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayWindow(QWidget *parent = nullptr);
    ~PlayWindow();
    int w_size,h_size;
    int candyLvl;

private:
    Ui::PlayWindow *ui;
    void StartGame();
    void Update();
    //QWidget *curent;
    QLabel *candyLvlLabel;
    QLabel *candyEatLabel;
    CandyWorld *candyWorld;
    QVector<QVector<int>> *worldMatrix;
    QVector<QVector<QWidget*>> *graphicsMatrix;
    QPalette *playerPalette;
    QPalette *candyPalette;
    QPalette *voidPalette;
    QPalette *wallPalette;
    void keyPressEvent(QKeyEvent *event);
};

#endif // PLAYWINDOW_H
