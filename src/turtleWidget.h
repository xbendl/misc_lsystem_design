/**
* \file turtleWidget.h
* 2D rastr pro zobrazeni obrazce urceneho vygenerovanymi pravidly.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef MAPWIDGET_H_INCLUDED
#define MAPWIDGET_H_INCLUDED

#include <QtGui>
#include <QWidget>
#include <QMetaType>
#include <QThread>
#include <QWaitCondition>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include "config.h"

/// 2D mrizka pro zobrazeni stavu bunek celularniho automatu.
class TurtleWidget : public QWidget
{
    Q_OBJECT

    QImage image;
    bool showImage;

    protected:
    void paintEvent(QPaintEvent *event);

    public:
    /**
    * Konstruktor.
    * @param parent Rodicovsky objekt.
    */
    TurtleWidget(QWidget *parent = 0);

    /**
    * Vykresli obraz dle zadaneho rastru
    * @param image Zadany rastr.
    */
    void SetImage(QImage image);

    /**
    * Vycisti rastr widgetu.
    */
    void ClearWidget();
};

#endif // MAPWIDGET_H_INCLUDED
