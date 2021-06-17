#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include<QtWidgets>
#include<candyworld.h>

QT_BEGIN_NAMESPACE
namespace Ui { class GameWindow; }
QT_END_NAMESPACE

class GameWindow: public QWidget
{
    Q_OBJECT

public:
    GameWindow(QWidget *parent = nullptr);
    ~GameWindow();
    int w_size,h_size;

private:
    void StartGame();
    void Update();
    Ui::GameWindow *ui;
    QWidget *parent;
    //QWidget *curent;
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

#endif // GAMEWINDOW_H
