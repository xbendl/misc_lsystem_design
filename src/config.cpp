#include "config.h"

using namespace std;

Config::Config()
{
    // Nastaveni vychozich parametru
    cIteration = 1;
    sPopulation = 40;
    nGenerations = 100;
    sElitism = 5;
    logInterval = 5;
    pMutation = 0.1;
    pInsertion = 0.25;
    pDeletion = 0.05;
    pMutationIteration = 0.1;
    pSelectReproduct = 0.25;
    pSelectDelete = 0.25;

    ruleLength = 10;
    iterationMax = 1;
    initIteration = 1;
    initAxiom = 'F';
    initAngle = (30 * M_PI / 180);

    imageSizeRect = 264;
    imageSize = 75;

    // Nastaveni mnoziny pouzivanych pravidel
    basicGrammar.push_back("F");
    basicGrammar.push_back("FF");
    basicGrammar.push_back("F+");
    basicGrammar.push_back("F-");
    basicGrammar.push_back("+F");
    basicGrammar.push_back("-F");
    basicGrammar.push_back("F+F");
    basicGrammar.push_back("F-F");
    basicGrammar.push_back("+");
    basicGrammar.push_back("-");
    basicGrammar.push_back("++");
    basicGrammar.push_back("--");
    basicGrammar.push_back("");
    basicGrammar.push_back("[F]F");

    initAxiomVector.push_back("F");
    initAxiomVector.push_back("FF");
    initAxiomVector.push_back("F+F");
    initAxiomVector.push_back("F-F");
    initAxiomVector.push_back("F+F+F");
    initAxiomVector.push_back("F-F-F");
}

Config::~Config()
{
    if(configInstance != 0)
        delete configInstance;
}

bool Config::LoadConfiguration(string configFile)
{
    unsigned int cutAt;
    string line, paramName, paramValue;
    ifstream file(configFile.c_str());

    if(!file.good())
    {
        cerr << "Chyba! Konfiguracni soubor nelze otevrit." << endl;
        exit(1);
    }

    while(getline(file, line))
    {
        if((cutAt = line.find_first_of("=")) == line.npos)   // neplatny radek konfiguracniho souboru
            continue;

        paramName = line.substr(0, cutAt);
        paramValue = line.substr(cutAt + 1);
        StringTrim(paramName);
        StringTrim(paramValue);

        if(paramName == "PROBLEM_FILE")
            problemFile = paramValue;
        else if(paramName == "S_POPULATION")
            sPopulation = atoi(paramValue.c_str());
        else if(paramName == "N_GENERATIONS")
            nGenerations = atoi(paramValue.c_str());
        else if(paramName == "P_MUTATION")
            pMutation = atof(paramValue.c_str());
        else if(paramName == "P_MUTATION_ITERATION")
            pMutationIteration = atof(paramValue.c_str());
        else if(paramName == "P_INSERTION")
            pInsertion = atof(paramValue.c_str());
        else if(paramName == "P_DELETION")
            pDeletion = atof(paramValue.c_str());
        else if(paramName == "P_SELECT_REPRODUCT")
            pSelectReproduct = atof(paramValue.c_str());
        else if(paramName == "P_SELECT_DELETE")
            pSelectDelete = atof(paramValue.c_str());
        else if(paramName == "S_ELITISM")
            sElitism = atoi(paramValue.c_str());
        else if(paramName == "LOG_INTERVAL")
            logInterval = atoi(paramValue.c_str());
        else if(paramName == "IMAGE_SIZE")
            imageSize = atoi(paramValue.c_str());
        else if(paramName == "RULE_LENGTH")
            ruleLength = atoi(paramValue.c_str());
        else if(paramName == "ITERATION_MAX")
            iterationMax = atoi(paramValue.c_str());
        else if(paramName == "INIT_ITERATION")
            initIteration = atoi(paramValue.c_str());
        else if(paramName == "INIT_AXIOM")
            initAxiom = paramValue;
        else if(paramName == "INIT_ANGLE")
            initAngle = atof(paramValue.c_str()) * M_PI / 180;
    }

    // Osetreni nespravne konfigurace
    if(sPopulation < sElitism)
    {
        cerr << "CHYBA! Pocet jedincu pro elitismus musi byt mensi nez velikost populace." << endl;
        exit(1);
    }

    file.close();

    return true;
}

void StringTrim(string& str)
{
    string::size_type pos1 = str.find_first_not_of(' ');
    string::size_type pos2 = str.find_last_not_of(' ');
    str = str.substr(pos1 == string::npos ? 0 : pos1, pos2 == string::npos ? str.length() - 1 : pos2 - pos1 + 1);
}

Config *Config::configInstance = 0;
