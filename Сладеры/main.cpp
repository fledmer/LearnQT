#include "mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <form.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Form *form = new Form;
    form->resize(400,400);
    form->show();

    return a.exec();
}
