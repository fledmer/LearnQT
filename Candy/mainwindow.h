#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <candyworld.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void ReDraw();

private:
    void keyPressEvent(QKeyEvent *event);
    QPixmap pxm;
    CandyWorld *game;
    QVector<QVector<int>> *world;
    QVector<QVector<QWidget*>> *graphics;
    Ui::MainWindow *ui;
    QPalette *playerPalette;
    QPalette *candyPalette;
    QPalette *voidPalette;
    int w_count;
    int h_count;
};
#endif // MAINWINDOW_H
