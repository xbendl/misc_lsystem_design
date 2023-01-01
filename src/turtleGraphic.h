/**
* \file turtleGraphic.h
* Modul pro praci s generovanymi obrazci.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef TURTLEGRAPHIC_H_INCLUDED
#define TURTLEGRAPHIC_H_INCLUDED

#include <QtGui>
#include <QWidget>
#include <math.h>
#include <stdlib.h>
#include <iostream>
#include "config.h"

/// Operace s generovanymi obrazci
class TurtleGraphic //: public QWidget
{
    QImage image;

    public:
    /**
    * Konstruktor.
    * @param parent Rodicovsky objekt.
    */
    TurtleGraphic();

    /**
    * Zmensi rozmery obrazku tak, aby se vesel do widgetu v okne.
    * @param image Puvodni obrazek.
    * @param scaledImage Zmenseny obrazek.
    * @param maxWidth Maximalni sirka zmenseneho obrazku.
    * @param maxHeight Maximalni vyska zmenseneho obrazku.
    */
    static void ScaleImage(QImage &image, QImage &scaledImage, int maxWidth, int maxHeight);

    /**
    * Orizne obrazek o prazdne sloupce a radky na okrajich.
    * @param pattern Orezavany obrazek.
    * @param croppedPattern Oriznuty obrazek.
    */
    static void CropImage(QImage &pattern, QImage &croppedPattern);

    /**
    * Vytvori obrazec podle zadaneho predpisu.
    * @param generatedString Retezec, podle ktereho bude generovani probihat.
    * @param angle Uhel, o ktery se zelva bude natacet.
    * @return Vygenerovany obrazec.
    */
    static QImage CreateImage(string generatedString, float angle);
};

#endif // TURTLEGRAPHIC_H_INCLUDED
