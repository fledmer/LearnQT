#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <playwindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Ловушка Ильи");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Play()
{
    PlayWindow *a = new PlayWindow();
    a->show();
}

void MainWindow::on_pushButton_pressed()
{
    Play();
    this->close();
}
