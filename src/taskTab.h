/**
* \file taskTab.h
* Zalozka pro tvorbu novych uloh.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef TASK_TAB_H_INCLUDED
#define TASK_TAB_H_INCLUDED

#include <QtGui>
#include <QWidget>
#include <qfiledialog.h>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <vector>
#include <stack>
#include <string>
#include <math.h>
#include <float.h>
#include "config.h"
#include "turtleWidget.h"
#include "turtleGraphic.h"

/// Zalozka s tvorbou novych uloh.
class TaskTab : public QWidget
{
    Q_OBJECT

    private:
    QPlainTextEdit *taskRulesTextBox;
    QPlainTextEdit *resultTextBox;
    QSpinBox *taskIteration;

    QPushButton *createNewTaskButton;
    QPushButton *saveNewTaskButton;
    QPushButton *loadTaskButton;

    TurtleWidget *taskViewWidget;      ///< Rastr pro zobrazeni vytvarene ulohy.
    vector<tExtendedRule> usedRules;   ///< Pravidla zpracovavaneho L-systemu.
    QImage *pattern;                   ///< Obrazek vytvoreny podle vygenerovaneho retezce.

    protected:
    void paintEvent(QPaintEvent *);

    public:
    /**
    * Konstruktor.
    */
    TaskTab(QWidget *parent = 0);

    /**
    * Destruktor.
    */
    ~TaskTab();

    private slots:
    /**
    * Zjisti od uzivatele cestu k souboru s ulohou.
    */
    void SetOpenFileName();

    /**
    * Vytvori nahled dle zadaneho pravidla a parametru.
    */
    void CreateNewTaskByRules();

    /**
    * Zjisti od uzivatele cestu k souboru, do ktereho budou ulozeny vysledky.
    */
    void SaveNewTask();

    private slots:
    /**
    * Zmena stavu polozky "Pocet iteraci".
    * newValue Novy stav policka.
    */
    void ChangeCIteration(int newValue);
};

#endif // TASK_TAB_H_INCLUDED
