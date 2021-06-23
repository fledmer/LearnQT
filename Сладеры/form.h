#ifndef FORM_H
#define FORM_H

#include <QWidget>

class Form : public QWidget
{
    Q_OBJECT
public:
    explicit Form(QWidget *parent = nullptr);

signals:
    void setNum(int);
    void setText(QString);
public slots:
    void getText(const QString &text);
    void getNum(const int num);
};

#endif // FORM_H
