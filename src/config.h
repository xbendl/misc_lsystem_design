/**
* \file config.h
* Spravce konfiguracnich udaju.
* \author Bendl Jaroslav (xbendl00)
*/

#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <math.h>

using namespace std;

/// Genom jednotlivce v populaci.
typedef struct
{
    int iteration;           ///< Pocet iteraci pro rozgenerovani pravidla.
    string rule;             ///< Prepisovaci pravidlo (ve forme retezce integeru).
    string transcriptRule;   ///< Prepisovaci pravidlo ve standardni forme.
    string generatedString;  ///< Rozgenerovane pravidlo (podoba zalezi na poctu iteraci).
    int price;               ///< Ohodnoceni jedince (rozdil vygenerovaneho obrazce oproti vzorovemu obrazci).
} tIndividual;

/// Rozsirena definice pravidla L-Systemu.
typedef struct
{
    char symbol;         ///< Prepisovany symbol.
    string rightSide;    ///< Nahrazujici retezec.
} tExtendedRule;

/// Stav zelvy.
typedef struct
{
    double x;       ///< Pozice zelvy na ose X.
    double y;       ///< Pozice zelvy na ose Y.
    double angle;   ///< Uhel natoceni zelvy.
} tTurtleState;

/// Spravce konfiguracnich udaju.
class Config
{
    private:
    /**
    * Konstruktor.
    */
    Config();

    /**
    * Destruktor.
    */
    ~Config();

    public:
    string configFile;         ///< Cesta ke konfiguracnimu souboru
    string problemFile;        ///< Cesta k souboru s resenym problemem.
    int cIteration;            ///< Pocet iteraci.
    int sPopulation;           ///< Velikost populace.
    int nGenerations;          ///< Pocet generaci.
    int sElitism;              ///< Pocet jedincu, u kterych se aplikuje elitismus.
    int logInterval;           ///< Pocet generaci, po kterych se budou zaznamenavat statisticky vyznamne hodnoty
    int imageSize;             ///< Rozmery ctverce pro zobrazeni grafickeho nahledu.
    int imageSizeRect;         ///< Rozmery ctverce pro zobrazeni grafickeho nahledu vcetne okraju.
    float pMutation;           ///< Pravdepodobnost mutace (obycejna mutace / fuze / vypusteni).
    float pInsertion;          ///< Pravdepodobnost inserce (vlozeni kodonu v ramci procesu mutace).
    float pDeletion;           ///< Pravdepodobnost delece (odstraneni kodonu v ramci procesu mutace).
    float pSelectReproduct;    ///< Mira nejlepsich jedincu urcenych k reprodukci (v ramci procesu krizeni).
    float pSelectDelete;       ///< Mira nejhorsich jedincu, kteri nebudou dale uvazovani v evolucnim procesu.
    float pMutationIteration;  ///< Pravdepodobnost mutace poctu iteraci.

    int ruleLength;            ///< Pocet integeru, z kterych bude sestaven pocatecni konstrukcni vektor.
    int iterationMax;          ///< Maximalni mozny pocet iteraci rozgenerovani pravidla
    int initIteration;         ///< Pocatecni pocet iteraci.
    string initAxiom;          ///< Pocatecni axiom.
    float initAngle;           ///< Pocatecni uhel.
    vector<string> basicGrammar;     ///< Zakladni gramatika - mnozina prepisovacich pravidel pro symbol 'F'
    vector<string> initAxiomVector;  ///< Mnozina moznych axiomu

    static Config *configInstance;      ///< Reference na instanci objektu

    /**
    * Nacte konfiguracni udaje z konfiguracniho souboru.
    * @param configFile Jmeno konfiguracniho souboru.
    * @return Udava, zda-li se nacteni konfiguracnich udaju podarilo.
    */
    bool LoadConfiguration(std::string configFile);

    /**
    * Vrati referenci na instanci objektu (pokud neexistuje, vytvori ji).
    * @return Reference na instanci objektu.
    */
    static Config *GetInstance()
    {
        if(!configInstance)
          configInstance = new Config;

        return configInstance;
    }
};

/**
 * Smaze prazdne znaky na zacatku a na konci retezce (prevzato z CodeProjects).
 * @param str Orezavany retezec.
 */
void StringTrim(string& str);


#endif // CONFIG_H_INCLUDED

