/**
* \file evolutionManagerTab.h
* Zalozka pro spravu evolucniho procesu.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef EVOLUTION_MANAGER_TAB_H_INCLUDED
#define EVOLUTION_MANAGER_TAB_H_INCLUDED

#include <QtGui>
#include <QWidget>
#include <iostream>
#include <iomanip>
#include "config.h"
#include "turtleWidget.h"
#include "evolutionManager.h"

/// Zalozka se spravou evolucniho procesu
class EvolutionManagerTab : public QWidget
{
    Q_OBJECT

    private:
    QLabel *taskNameLabel;

    QPushButton *loadTaskButton;
    QPushButton *evoluteStartButton;
    QPushButton *evoluteStopButton;
    QPushButton *evoluteAbortButton;
    QPushButton *saveResultButton;

    QSpinBox *sPopulationStepLine;
    QSpinBox *nGenerationsStepLine;
    QSpinBox *sElitismStepLine;
    QSpinBox *logIntervalStepLine;
    QDoubleSpinBox *pMutationDoubleSpinBox;
    QDoubleSpinBox *pInsertionDoubleSpinBox;
    QDoubleSpinBox *pDeletionDoubleSpinBox;
    QDoubleSpinBox *pSelectReproductDoubleSpinBox;

    QPlainTextEdit *resultTextBox;

    QProgressBar *evolutionProgressBar;

    TurtleWidget *patternWidget;        ///< Rastr pro zobrazeni predlohy.
    TurtleWidget *solutionWidget;       ///< Rastr pro zobrazeni aktualniho reseni v dane generaci.

    EvolutionManager evolutionManager;  ///< Spravce procesu evoluce pravidel L-Systemu.
    QImage pattern;                     ///< Vzorovy obrazek, jehoz napodobenina se vytvari pomoci evoluce L-systemu.
    tIndividual resultIndividual;       ///< Jedinec s nejlepsim fitness v ramci celeho evolucniho behu.
    /**
     * Vrati retezec s predanym cislem a prislusnym poctem prazdnych znaku.
     * @param number Predane cislo, ktere ma byt do retezce umisteno.
     * @param spaceCount Pocet znaku, ktere ma vysledny retezec dohromady zabirat.
     * @return Vytvoreny retezec s predanym cislem a prislusnym poctem prazdnych znaku.
     */
    string GetAlignString(int number, int spaceCount);

    protected:
    void paintEvent(QPaintEvent *);

    public:
    /**
    * Konstruktor.
    */
    EvolutionManagerTab(QWidget *parent = 0);

    private slots:
    /**
    * Zjisti od uzivatele cestu k souboru s ulohou.
    */
    void SetOpenFileName();

    /**
    * Zjisti od uzivatele cestu k souboru, do ktereho budou ulozeny vysledky.
    */
    void SetResultFile();

    /**
    * Spusti proces evoluce pravidel.
    */
    void StartEvolution();

    /**
    * Pozastavi proces evoluce pravidel.
    */
    void StopEvolution();

    /**
    * Zrusi proces evoluce pravidel.
    */
    void AbortEvolution();

    /**
    * Zmena stavu polozky "Velikost populace".
    * newValue Novy stav policka.
    */
    void ChangeSPopulation(int newValue);

    /**
    * Zmena stavu polozky "Pocet generaci".
    * newValue Novy stav policka.
    */
    void ChangeNGenerations(int newValue);

    /**
    * Zmena stavu polozky "Pravdepodobnost mutace".
    * newValue Novy stav policka.
    */
    void ChangePMutation(double newValue);

    /**
    * Zmena stavu polozky "Pravdepodobnost inserce".
    * newValue Novy stav policka.
    */
    void ChangePInsertion(double newValue);

    /**
    * Zmena stavu polozky "Pravdepodobnost delece".
    * newValue Novy stav policka.
    */
    void ChangePDeletion(double newValue);

    /**
    * Zmena stavu polozky "Vyber pro reprodukci".
    * newValue Novy stav policka.
    */
    void ChangePSelectReproduct(double newValue);

    /**
    * Zmena stavu polozky "Elitismus".
    * newValue Novy stav policka.
    */
    void ChangeSElitism(int newValue);

    /**
    * Zmena stavu polozky "Log interval".
    * newValue Novy stav policka.
    */
    void ChangeLogInterval(int newValue);

    /**
    * Prijme informaci o aktualnim stavu evolucniho vypoctu.
    * @param resultImage Nejlepsi reseni (v podobe obrazce) nalezene v aktualnim evolucnim kroku.
    * @param resultIndividual Nejlepsi jedinec v aktualnim evolucnim kroku.
    * @param actGeneration Cislo aktualni generace.
    * @param minCurrentImagePrice Nejlepsi cena reseni v aktualnim evolucnim kroku.
    * @param avgCurrentImagePrice Prumerna cena reseni v aktualnim evolucnim kroku.
    * @param maxCurrentImagePrice Nejhorsi cena reseni v aktualnim evolucnim kroku.
    */
    void ReceiveCurrentImageGenerated(QImage resultImage, tIndividual resultIndividual, int actGeneration, int minCurrentImagePrice, int avgCurrentImagePrice, int maxCurrentImagePrice);

    /**
    * Prijme informaci o stavu dokonceneho evolucniho vypoctu.
    * @param resultImage Nejlepsi nalezene reseni - v podobe obrazce.
    * @param resultIndividual Nejlepsi nalezeny jedinec.
    */
    void ReceiveImageGenerated(QImage resultImage, tIndividual resultIndividual);
};

#endif // EVOLUTION_MANAGER_TAB_H_INCLUDED
