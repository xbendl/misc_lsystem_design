/**
* \file evolutionManager.h
* Modul pro vypocet pravidel tvorby podobneho obrazce.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef EVOLUTIONMANAGER_H_INCLUDED
#define EVOLUTIONMANAGER_H_INCLUDED

#include <QMetaType>
#include <QThread>
#include <QMutex>
#include <QWaitCondition>
#include <QtGui>
#include <QDialog>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
#include "config.h"
#include "turtleGraphic.h"

/// Trida pro optimalizaci trasy obchodniho cestujiciho.
class EvolutionManager : public QThread
{
    Q_OBJECT

    private:

    /// Vysledky vypoctu.
    typedef struct
    {
        int crossoverCount;         ///< Pocet aplikaci operatoru krizeni od inicializace.
        int mutationCount;          ///< Pocet aplikaci operatoru mutace od inicializace.
        int insertionCount;         ///< Pocet aplikaci operatoru mutace - pridani kodonu - od inicializace.
        int deletionCount;          ///< Pocet aplikaci operatoru mutace - smazani kodonu - od inicializace.
        int genomeEvaluationCount;  ///< Pocet ohodnoceni genomu od inicializace.

        int avgImagePrice;          ///< Prumerna cena od inicializace.
        int maxImagePrice;          ///< Maximalni cena od inicializace.
        int minImagePrice;          ///< Minimalni cene od inicializace.

        int avgInitialImagePrice;   ///< Prumerna cena v pocatecni populaci.
        int minInitialImagePrice;   ///< Nejlepsi cena v pocatecni populaci.
        int maxInitialImagePrice;   ///< Nejhorsi cena v pocatecni populaci.

        int avgCurrentImagePrice;   ///< Prumerna cena v aktualni populaci.
        int minCurrentImagePrice;   ///< Nejlepsi cena v aktualni populaci.
        int maxCurrentImagePrice;   ///< Nejhorsi cena v aktualni populaci.
        struct timeval runningTime;   ///< Cas behu vypoctu.
    } tResult;

    tResult result;                  ///< Vysledky vypoctu.
    int actGeneration;               ///< Cislo aktualni generace behu evoluce.
    vector<tIndividual> parentPop;   ///< Populace rodicu.
    vector<tIndividual> childPop;    ///< Populace potomku.
    vector<tIndividual> tempPop;     ///< Smisena populace rodicu a potomku vybrana do dalsiho cyklu behu GA.
    QImage pattern;                  ///< Vzorovy obrazek, jehoz napodobenina se vytvari pomoci evoluce L-systemu.
    QImage individual;               ///< Napodobenina obrazku vytvorena evoluci L-Systemu.
    struct timeval startTime;        ///< Cas zacatku spusteni vypoctu.
    tIndividual resultIndividual;    ///< Jedinec s nejlepsim fitness v ramci celeho evolucniho behu.
    vector<float> tempAvgImagePrice;
    vector<float> tempMinImagePrice;
    vector<float> tempMaxImagePrice;

    bool abortFlag;                  ///< Priznak ukonceni evolucnich vypoctu
    bool sleepFlag;                  ///< Priznak pozastaveni evolucnich vypoctu

    QMutex mutex;
    QWaitCondition condition;

    /**
    * Smycka evolucniho vypoctu.
    */
    void run();

    /**
     * Ohodnoti populaci jedincu.
     * @param population Populace jedincu.
     */
    void EvaluatePopulation(vector<tIndividual> &population);

    /**
     * Ohodnoti jedince v populaci.
     * @param individual Ohodnocovany jedinec v populaci.
     */
    void EvaluateGenome(tIndividual &individual);

    /**
     * Ohodnoti jedince v populaci.
     * @param individual Ohodnocovany jedinec v populaci.
     */
    int FindNearestPixel(QImage *comparedImage, QPoint point);

    /**
     * Vytvori populaci jedincu (mnozinu permutaci mest).
     */
    void GenerateInitPopulation();

    /**
     * Vytvori retezec pro vykresleni vysledneho obrazce.
     * @param individual Genom jedince, podle ktereho bude vysledny retezec konstruovan.
     * @return Retezec pro vykresleni vysledneho obrazce.
     */
    string CreateTargetString(tIndividual &individual);

    /**
     * Ulozi vysledky k dane generaci behu vypoctu
     */
    void SetGenerationStatistics();

    /**
     * Provede krizeni nad predanou populaci.
     * @param population Populace, nad kterou krizeni probiha.
     * @param pSelectReproduct Cast nejlepsich jedincu uvazovanych jako rodice pro krizeni.
     * @param pSelectDelete Cast nejhorsich jedincu urcenych pro nahradu.
     */
    void Crossover(vector<tIndividual> &parentPop, float pSelectReproduct, float pSelectDelete);

    /**
     * Provede mutaci nad predanou populaci.
     * @param population Populace, nad kterou mutace probiha.
     * @param sElitism Pocet nejlepsich jedincu, na ktere se mutace nevztahuje.
     */
    void Mutation(vector<tIndividual> &population, int sElitism);

    /**
     * Ziska cislo aktualni generace behu vypoctu.
     * @return Urcuje, zda-li jiz bylo dosazeno pozadovaneho poctu generaci.
     */
    bool Done();

    /**
     * Provede jeden evolucni krok.
     */
    void Step();

    /**
    * Orizne obrazek o prazdne sloupce a radky na okrajich.
    * @param pattern Orezavany obrazek.
    * @param croppedPattern Oriznuty obrazek.
    */
    void CropImage(QImage *pattern, QImage &croppedPattern);

    /**
    * Zmensi rozmery obrazku tak, aby se vesel do widgetu v okne.
    * @param image Puvodni obrazek.
    * @param scaledImage Zmenseny obrazek.
    */
    void ScaleImage(QImage &image, QImage &scaledImage);

    public:

    /**
    * Hleda pravidla L-Systemu schopna generovat obrazec podobny vzorovemu obrazci.
    * @param pattern Vzorovy obrazec.
    */
    void FindSolution(QImage pattern);

    /**
    * Pozastavi evoluci pravidel.
    */
    void StopEvolution();

    /**
    * Zrusi evoluci pravidel.
    */
    void AbortEvolution();

    /**
     * Ulozi vysledky behu vypoctu.
     * @param outputFile Cesta k vystupimu souboru, do ktereho budou ulozeny vysledky behu evoluce.
     * @return Urcuje, zda-li se zapsani vysledku do vystupniho souboru podarilo.
     */
    bool SaveResults(string outputFile);

    /**
    * Konstruktor.
    * @param parent Rodicovsky objekt.
    */
    EvolutionManager(QObject *parent = 0);

    /**
     * Destruktor.
     */
    ~EvolutionManager();

    signals:
    /**
    * Signal zaslany po provedeni urceneho poctu evolucnich kroku.
    * @param resultImage Nejlepsi reseni (v podobe obrazce) nalezene v aktualnim evolucnim kroku.
    * @param resultIndividual Nejlepsi jedinec v aktualnim evolucnim kroku.
    * @param actGeneration Cislo aktualni generace.
    * @param minCurrentImagePrice Nejlepsi cena reseni v aktualnim evolucnim kroku.
    * @param avgCurrentImagePrice Prumerna cena reseni v aktualnim evolucnim kroku.
    * @param maxCurrentImagePrice Nejhorsi cena reseni v aktualnim evolucnim kroku.
    */
    void CurrentImageGenerated(QImage resultImage, tIndividual resultIndividual, int actGeneration, int minCurrentImagePrice, int avgCurrentImagePrice, int maxCurrentImagePrice);

    /**
    * Signal zaslany po dokonceni behu evoluce.
    * @param resultImage Nejlepsi nalezene reseni - v podobe obrazce.
    * @param resultIndividual Nejlepsi nalezeny jedinec.
    */
    void ImageGenerated(QImage resultImage, tIndividual resultIndividual);
};

/**
 * Porovna dva ruzne jedince na zaklade jejich ohodnoceni.
 * @param inv1 Prvni porovnavany jedinec.
 * @param inv2 Druhy porovnavany jedinec.
 * @return True, pokud je cena ohodnoceni prvniho jedince mensi nez ohodnoceni druheho jedince.
 */
bool FitnessSort(tIndividual inv1, tIndividual inv2);

#endif // EVOLUTIONMANAGER_H_INCLUDED
