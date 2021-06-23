#include "form.h"
#include "QSlider"
#include "QLCDNumber"
#include "QSlider"
#include "QVBoxLayout"
#include "QScrollBar"
#include "QStyle"
#include "QDial"
#include "QLabel"

Form::Form(QWidget *parent) : QWidget(parent)
{
    QLCDNumber *lcdNumber = new QLCDNumber();
    lcdNumber->setSegmentStyle(QLCDNumber::Flat);
    //lcdNumber->setPalette(Qt::darkGreen);
    lcdNumber->setFont(QFont("Times New Roman"));
    lcdNumber->setStyleSheet("color: #009a63");
    lcdNumber->setMode(QLCDNumber::Hex);

    QFont baseLabelFont("Times New Roman",15);

    QLabel *sliderLabel = new QLabel("&Слайдер:");
    sliderLabel->setFont(baseLabelFont);
    QSlider *slider = new QSlider(Qt::Horizontal);
    sliderLabel->setBuddy(slider);
    slider->setRange(0,100);
    slider->setTickPosition(QSlider::TicksBothSides);
    slider->setTickInterval(10);
    connect(slider,SIGNAL(valueChanged(int)),lcdNumber,SLOT(display(int)));

    QLabel *scrollBarLabel = new QLabel("&Ползунок:");
    scrollBarLabel->setFont(baseLabelFont);
    QScrollBar *scrollBar = new QScrollBar(Qt::Horizontal);
    scrollBarLabel->setBuddy(scrollBar);
    scrollBar->setRange(0,100);
    scrollBar->setStyleSheet(
   "QScrollBar:horizontal { \
    border: 2px solid grey; \
    background: #BCAAA4; \
    height: 30px; \
    margin: 0px 0px 0px 0px;}");
    connect(scrollBar,SIGNAL(valueChanged(int)),lcdNumber,SLOT(display(int)));
    connect(scrollBar,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)),scrollBar,SLOT(setValue(int)));

    QLabel *dialLabel = new QLabel("&Беляшек:");
    dialLabel->setFont(baseLabelFont);
    QDial *dial = new QDial();
    dialLabel->setBuddy(scrollBarLabel);
    dial->setRange(0,100);
    dial->setNotchTarget(10);
    dial->setNotchesVisible(true);
    connect(dial,SIGNAL(valueChanged(int)),lcdNumber,SLOT(display(int)));
    connect(dial,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));
    connect(dial,SIGNAL(valueChanged(int)),scrollBar,SLOT(setValue(int)));
    connect(slider,SIGNAL(valueChanged(int)),dial,SLOT(setValue(int)));
    connect(scrollBar,SIGNAL(valueChanged(int)),dial,SLOT(setValue(int)));

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(lcdNumber);
    mainLayout->addWidget(sliderLabel);
    mainLayout->addWidget(slider);
    mainLayout->addWidget(scrollBarLabel);
    mainLayout->addWidget(scrollBar);
    mainLayout->addWidget(dialLabel);
    mainLayout->addWidget(dial);
    setLayout(mainLayout);
}
