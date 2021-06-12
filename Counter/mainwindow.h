#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLCDNumber>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLCDNumber *LCDcouter;
    Ui::MainWindow *ui;
    int couter;

public slots:
    void plusSlot();
    void minusSlot();
};
#endif // MAINWINDOW_H
