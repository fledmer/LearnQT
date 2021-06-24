#include "form.h"
#include "QSlider"
#include "QLCDNumber"
#include "QSlider"
#include "QVBoxLayout"
#include "QScrollBar"
#include "QStyle"
#include "QDial"
#include "QLabel"
#include "QGroupBox"
#include "QLineEdit"
#include "QTextEdit"
#include "MyHighlighter.h"
#include "QPushButton"

Form::Form(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(1);
    setLayout(mainLayout);
    QFont baseLabelFont("Times New Roman",15);

    QSlider *slider;
    {
    QGroupBox *firstGroupBox = new QGroupBox("Штуки-дрюки",this);
    mainLayout->addWidget(firstGroupBox);
    setLayout(mainLayout);

    QLCDNumber *lcdNumber = new QLCDNumber();
    lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    //lcdNumber->setPalette(Qt::darkGreen);
    lcdNumber->setFont(QFont("Times New Roman"));
    lcdNumber->setStyleSheet("color: #009a63");
    lcdNumber->setMode(QLCDNumber::Hex);


    QLabel *sliderLabel = new QLabel("&Слайдер:");
    sliderLabel->setFont(baseLabelFont);
    slider = new QSlider(Qt::Horizontal);
    sliderLabel->setBuddy(slider);
    slider->setRange(0,100);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    slider->setStyleSheet(
                "QSlider::groove:horizontal {\
                    border: 1px solid #999999;\
                    height: 8px;\
                    background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 #007c00, stop:1 #00e400);\
                    margin: 2px 0;\
                }\
                QSlider::handle:horizontal {\
                    background: qlineargradient(x1:0, y1:0, x2:1, y2:1, stop:0 #00e400, stop:1 #007c00);\
                    border: 1px solid #5c5c5c;\
                    width: 18px;\
                    margin: -2px 0;\
                    border-radius: 3px;\
                };");
    connect(slider,SIGNAL(valueChanged(int)),lcdNumber,SLOT(display(int)));

    QLabel *scrollBarLabel = new QLabel("&Ползунок:");
    scrollBarLabel->setFont(baseLabelFont);
    QScrollBar *scrollBar = new QScrollBar(Qt::Horizontal);
    scrollBarLabel->setBuddy(scrollBar);
    scrollBar->setRange(0,100);
    scrollBar->setStyleSheet(
                   "QScrollBar:horizontal { \
                    border: 2px solid grey; \
                    background: #00c500; \
                    height: 30px; \
                    margin: 0px 20px 0 20px; \
                } \
                QScrollBar::handle:horizontal { \
                    min-width: 20px; \
                } \
                QScrollBar::add-line:horizontal { \
                    border: 2px solid grey; \
                    background: #00c500; \
                    width: 20px; \
                    subcontrol-position: right; \
                    subcontrol-origin: margin; \
                } \
                QScrollBar::sub-line:horizontal { \
                    border: 2px solid grey; \
                    background: #00c500; \
                    width: 20px; \
                    subcontrol-position: left; \
                    subcontrol-origin: margin; \
                }; ");
    connect(scrollBar,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)),scrollBar,SLOT(setValue(int)));

    QLabel *dialLabel = new QLabel("&Беляшек:");
    dialLabel->setFont(baseLabelFont);
    QDial *dial = new QDial();
    dialLabel->setBuddy(scrollBarLabel);
    dial->setRange(0,100);
    dial->setNotchTarget(10);
    dial->setNotchesVisible(true);
    dial->setPalette(Qt::darkGreen);
    connect(dial,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)),dial,SLOT(setValue(int)));

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(lcdNumber);
    verticalLayout->addWidget(sliderLabel);
    verticalLayout->addWidget(slider);
    verticalLayout->addWidget(scrollBarLabel);
    verticalLayout->addWidget(scrollBar);
    verticalLayout->addWidget(dialLabel);
    verticalLayout->addWidget(dial);
    firstGroupBox->setLayout(verticalLayout);
    }
    //Растягивается через очко
    {
    QGroupBox *groupBox = new QGroupBox("Двоичная выводилка");
    QVBoxLayout *boxLayout = new QVBoxLayout;
    QLCDNumber *lcdNumber = new QLCDNumber();
    lcdNumber->setFont(QFont("Times New Roman",15));
    lcdNumber->setStyleSheet("color: #009a63");
    lcdNumber->setMode(QLCDNumber::Bin);
    connect(slider,SIGNAL(valueChanged(int)),lcdNumber,SLOT(display(int)));
    boxLayout->addWidget(lcdNumber);
    groupBox->setLayout(boxLayout);
    mainLayout->addWidget(groupBox);
    }

    {
    QGroupBox *groupBox = new QGroupBox("Писанина");
    mainLayout->addWidget(groupBox);

    QLabel *lineEditLabel = new QLabel("&Редактор строки");
    lineEditLabel->setFont(baseLabelFont);
    QLineEdit *lineEdit = new QLineEdit();
    lineEditLabel->setBuddy(lineEditLabel);
    lineEdit->setFrame(true);
    connect(lineEdit,SIGNAL(textChanged(QString)),SLOT(getText(QString)));
    connect(this, SIGNAL(setNum(int)),slider,SLOT(setValue(int)));
    connect(slider, SIGNAL(valueChanged(int)),this,SLOT(getNum(int)));
    connect(this, SIGNAL(setText(QString)),lineEdit,SLOT(setText(QString)));

    QLabel *textEditLabel = new QLabel("Редактор &текста");
    textEditLabel->setFont(baseLabelFont);
    QTextEdit *textEdit = new QTextEdit();
    QPalette *palette = new QPalette();
    palette->setColor(QPalette::Base,Qt::darkBlue);
    palette->setColor(QPalette::Text,Qt::yellow);
    textEdit->setPalette(*palette);
    textEditLabel->setBuddy(textEdit);
    textEdit->setFrameStyle(QFrame::Sunken | QFrame::StyledPanel);
    new MyHighLighter(textEdit->document());
    QHBoxLayout *horizontalLayout;
    {
        QPushButton *minusButton = new QPushButton("-");
        connect(minusButton,SIGNAL(pressed()),textEdit,SLOT(zoomOut()));
        QPushButton *plusButton = new QPushButton("+");
        connect(plusButton,SIGNAL(pressed()),textEdit,SLOT(zoomIn()));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->addWidget(minusButton);
        horizontalLayout->addWidget(plusButton);
    }

    QVBoxLayout *verticalLayout = new QVBoxLayout;
    verticalLayout->addWidget(lineEditLabel);
    verticalLayout->addWidget(lineEdit);
    verticalLayout->addWidget(textEditLabel);
    verticalLayout->addWidget(textEdit);
    verticalLayout->addLayout(horizontalLayout);
    groupBox->setLayout(verticalLayout);
    }
}


void Form::getText(const QString &text)
{
    QVariant converter(text);
    bool suc;
    converter.toInt(&suc);

    if(suc){
        emit setNum(converter.toInt());
    }

}

void Form::getNum(const int num)
{
    QVariant converter(num);
    emit setText(converter.toString());
}
