#include "evolutionManager.h"

using namespace std;

EvolutionManager::EvolutionManager(QObject *) : QThread()
{
    // Nastaveni priznaku ukonceni a uspani
    abortFlag = false;
    sleepFlag = false;

    // Priprava pouzivanych vektoru ve vypoctu
    parentPop.clear();
    childPop.clear();
    tempPop.clear();
    tempMinImagePrice.clear();
    tempAvgImagePrice.clear();
    tempMaxImagePrice.clear();
    actGeneration  = 0;

    result.minImagePrice = result.minInitialImagePrice = result.minCurrentImagePrice = INT_MAX;
    result.crossoverCount = result.mutationCount = result.insertionCount = result.deletionCount =
        result.genomeEvaluationCount = result.avgImagePrice = result.avgInitialImagePrice =
        result.avgCurrentImagePrice = result.maxImagePrice = result.maxInitialImagePrice =
        result.maxCurrentImagePrice = 0;
}

EvolutionManager::~EvolutionManager()
{
    mutex.lock();
    abortFlag = true;      // Nastaveni priznaku pro ukonceni
    condition.wakeOne();   // Probuzeni spiciho vlakna
    mutex.unlock();

    wait();                // Pockani na dobehnuti vlakna
}

void EvolutionManager::FindSolution(QImage pattern)
{
    this->pattern = pattern;
    Config::GetInstance()->initAxiom = Config::GetInstance()->initAxiomVector[rand() % Config::GetInstance()->initAxiomVector.size()];

    // Priprava pouzivanych vektoru ve vypoctu
    parentPop.clear();
    childPop.clear();
    tempPop.clear();
    tempMinImagePrice.clear();
    tempAvgImagePrice.clear();
    tempMaxImagePrice.clear();
    actGeneration  = 0;

    result.minImagePrice = result.minInitialImagePrice = result.minCurrentImagePrice = INT_MAX;
    result.crossoverCount = result.mutationCount = result.insertionCount = result.deletionCount =
        result.genomeEvaluationCount = result.avgImagePrice = result.avgInitialImagePrice =
        result.avgCurrentImagePrice = result.maxImagePrice = result.maxInitialImagePrice =
        result.maxCurrentImagePrice = 0;

    // Nastaveni priznaku ukonceni a uspani
    this->abortFlag = false;
    this->sleepFlag = false;

    // Spusteni evoluce
    if(!isRunning())
        start();
}

void EvolutionManager::run()
{
    GenerateInitPopulation();      // vytvori pocatecni populaci jedincu

    while(!Done())
    {
        cout << actGeneration << " ";
        cout.flush();

        Step();

        if(actGeneration % Config::GetInstance()->logInterval == 0)
        {   // prubezne vypisovani aktualni generace vypoctu
            SetGenerationStatistics();
            cout.flush();

            mutex.lock();
            if(!abortFlag)
            {
                QImage resultImage = TurtleGraphic::CreateImage(resultIndividual.generatedString, Config::GetInstance()->initAngle);  // vykresleni obrazce podle vygenerovaneho retezce
                emit CurrentImageGenerated(resultImage, resultIndividual, actGeneration, result.minCurrentImagePrice, result.avgCurrentImagePrice, result.maxCurrentImagePrice);
            }
            mutex.unlock();
        }

        // Uspani pri nastaveni priznaku uspani
        mutex.lock();
        if(sleepFlag)
        {
            condition.wait(&mutex);
            sleepFlag = false;
        }
        mutex.unlock();

        // Ukonceni pri nastaveni priznaku ukonceni
        mutex.lock();
        if(abortFlag)
        {
            // Vypocet a ulozeni doby behu
            struct timeval endTime;
            gettimeofday(&endTime, NULL);
            result.runningTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
            if((endTime.tv_usec - startTime.tv_usec) < 0)
            {
                result.runningTime.tv_sec--;
                result.runningTime.tv_usec = (startTime.tv_usec - endTime.tv_usec) + 1;
            }
            else
            {
                result.runningTime.tv_usec = endTime.tv_usec - startTime.tv_usec;
            }
            mutex.unlock();
            return;
        }
        mutex.unlock();
    }

    // Vygenerovani signalu; zasilame nejlepsiho nalezeneho jedince
    QImage resultImage = TurtleGraphic::CreateImage(resultIndividual.generatedString, Config::GetInstance()->initAngle);  // vykresleni obrazce podle vygenerovaneho retezce
    emit ImageGenerated(resultImage, resultIndividual);
}

void EvolutionManager::GenerateInitPopulation()
{
    int ruleLength = Config::GetInstance()->ruleLength;
    int randomValue;

    tIndividual individual;
    individual.price = 0;
    individual.iteration = Config::GetInstance()->initIteration;

    // Generovani pravidla pro kazdeho jedince populace.
    for(int i = 0; i < Config::GetInstance()->sPopulation; i++)
    {
        // Generovani vektoru integeneru
        individual.rule.clear();
        for(int j = 0; j < ruleLength; j++)
        {
            randomValue = rand() % CHAR_MAX;
            individual.rule += randomValue;
        }

        parentPop.push_back(individual);
    }

    // Ohodnoceni pocatecni populace jedincu
    EvaluatePopulation(parentPop);

    // Ulozeni statistik pocatecni populace jedincu
    result.minInitialImagePrice = INT_MAX;
    result.maxInitialImagePrice = 0;
    result.avgInitialImagePrice = 0;
    for(int i = 0; i < (int)parentPop.size(); i++)
    {
        if(parentPop[i].price > result.maxInitialImagePrice)
        {
            result.maxInitialImagePrice = parentPop[i].price;
            result.maxImagePrice = parentPop[i].price;
        }
        if(parentPop[i].price < result.minInitialImagePrice)
        {
            result.minInitialImagePrice = parentPop[i].price;
            result.minImagePrice = parentPop[i].price;
            resultIndividual = parentPop[i];
        }
        result.avgInitialImagePrice += parentPop[i].price;
    }
    result.avgInitialImagePrice = result.avgInitialImagePrice / parentPop.size();
    result.avgImagePrice = result.avgInitialImagePrice;
    tempMinImagePrice.push_back(result.minInitialImagePrice);
    tempAvgImagePrice.push_back(result.avgInitialImagePrice);
    tempMaxImagePrice.push_back(result.maxInitialImagePrice);

    mutex.lock();
    if(!abortFlag)
    {
        // Retezec integeru => Pravidlo L-Systemu => Retezec pro vykresleni
        CreateTargetString(resultIndividual);
        if(!resultIndividual.generatedString.empty())
        {   // Retezec pro vykresleni => Obrazek
            QImage resultImage = TurtleGraphic::CreateImage(resultIndividual.generatedString, Config::GetInstance()->initAngle);  // vykresleni obrazce podle vygenerovaneho retezce
            emit CurrentImageGenerated(resultImage, resultIndividual, actGeneration, result.minInitialImagePrice, result.avgInitialImagePrice, result.maxInitialImagePrice);
        }
    }
    mutex.unlock();
}

string EvolutionManager::CreateTargetString(tIndividual &individual)
{
    // Retezec integeru => Pravidlo L-Systemu
    string rule = Config::GetInstance()->initAxiom;
    string dummyRule = "";
    int actRuleIndex = 0;
    bool repeatSign = true;

    while(repeatSign)
    {
        dummyRule = "";

        // Generovani axiomu
        for(int i = 0; i < (int)rule.size(); i++)
        {
            if(rule[i] == 'F')
            {
                dummyRule += Config::GetInstance()->basicGrammar[individual.rule[actRuleIndex] % Config::GetInstance()->basicGrammar.size()];
                actRuleIndex++;
                if((actRuleIndex % Config::GetInstance()->ruleLength) == 0)
                    repeatSign = false;
            }
            else
            {
                dummyRule += rule[i];
            }
        }

        // Osetreni situace, kdy v retezci neni zadny element 'F'
        if(dummyRule.find('F') == string::npos)
            rule = 'F';
        else
            rule = dummyRule;
    }

    // Smazani nefunkcnich zavorek - typu [++] ci [F]
    int firstBracket = 0, elementF = 0, elementRotate = 0;
    for(int i = 0; i < (int)rule.size(); i++)
    {
        if(rule[i] == '[')
        {
            elementF = 0;
            elementRotate = 0;
            firstBracket = i;
        }
        else if((rule[i] == ']') && ((elementRotate == 0) || (elementF == 0)))
        {
            rule.erase(rule.begin() + firstBracket, rule.begin()+i+1);
            i = -1;
        }
        else if((rule[i] == '+') || (rule[i] == '-'))
        {
            elementRotate++;
        }
        else if(rule[i] == 'F')
        {
            elementF++;
        }
    }
    // Smazani + a - na koncich pravidla
    int cutAt;
    while((rule[rule.size() - 1] == '+') || (rule[rule.size() - 1] == '-'))
        rule.erase(rule.begin() + rule.size() - 1);

    // Smazani +- a -+ v pravidle
    while(((cutAt = rule.find("+-")) != (int)string::npos) || ((cutAt = rule.find("-+")) != (int)string::npos))
        rule.erase(rule.begin() + cutAt, rule.begin() + cutAt+2);

    individual.transcriptRule = rule;

    // Pravidlo L-Systemu => Obrazek
    string dummyWord;
    string word = (Config::GetInstance())->initAxiom;

    for(int i = 0; i < individual.iteration; i++)
    {
        dummyWord = "";
        for(int j = 0; j < (int)word.size(); j++)
        {
            if(word[j] == 'F')
                dummyWord += rule;
            else
                dummyWord += word[j];
        }
        word = dummyWord;
    }

    //cout << "Generated word: " << word << endl;

    return word;
}

void EvolutionManager::EvaluatePopulation(vector<tIndividual> &population)
{
    for(int i = 0; i < (int)population.size(); i++)
    {   // ohodnoti se vsechny jedinci populace
        EvaluateGenome(population[i]);
    }
}

void EvolutionManager::EvaluateGenome(tIndividual &individual)
{
    result.genomeEvaluationCount++;

    // Retezec integeru => Pravidlo L-Systemu => Retezec pro vykresleni
    if((individual.generatedString = CreateTargetString(individual)) == "")
    {   // je-li pravidlo prazdne, automaticky se mu priradi nejhorsi mozna fitness
        individual.price = pattern.width() * pattern.height() * pattern.width();
        return;
    }

    // Retezec pro vykresleni => Obrazek
    QImage individualImage = TurtleGraphic::CreateImage(individual.generatedString, Config::GetInstance()->initAngle);  // vykresleni obrazce podle vygenerovaneho retezce

    // Fitness se urci podle rozdilu v porovnavanych obrazcich
    QImage *patternImage, *comparedImage;
    individual.price = 0;

    for(int i = 0; i < 2; i++)
    {
        patternImage  = (i == 0) ? &pattern         : &individualImage;
        comparedImage = (i == 0) ? &individualImage : &pattern;

        for(int j = 0; j < patternImage->width(); j++)
        {
            for(int k = 0; k < patternImage->height(); k++)
            {
                if(qRed(patternImage->pixel(j, k)) == 0)
                    individual.price += FindNearestPixel(comparedImage, QPoint(j, k));
            }
        }
    }

    //cout << "Price: " << individual.price << endl;
}

int EvolutionManager::FindNearestPixel(QImage *comparedImage, QPoint point)
{
    int size = (comparedImage->width() > comparedImage->height()) ? comparedImage->width() : comparedImage->height();
    int price = 0;
    int minX, maxX, minY, maxY;

    // Hledani nejblizsiho vyplneneho bodu s postupnym rozsirovanim prohledavane oblasti
    for(int i = 0; i < size; i++)
    {
        // Urceni okrajovych souradnic prohledavaneho ctverce
        minX = ((point.x() - i) > 0) ? (point.x() - i) : 0;
        maxX = ((point.x() + i) < comparedImage->width()) ? (point.x() + i) : (comparedImage->width() - 1);
        minY = ((point.y() - i) > 0) ? (point.y() - i) : 0;
        maxY = ((point.y() + i) < comparedImage->height()) ? (point.y() + i) : (comparedImage->height() - 1);

        // Hledani ve vymezenem ctverci
        for(int j = minX; j <= maxX; j++)
            for(int k = minY; k <= maxY; k++)
                if(qRed(comparedImage->pixel(j, k)) == 0)
                    return price;

        price++;
    }

    return size;
}


bool EvolutionManager::Done()
{
    bool done = (actGeneration == Config::GetInstance()->nGenerations);

    // Akce po skonceni vypoctu
    if(done)
    {
        // Vypocet a ulozeni doby behu
        struct timeval endTime;
        gettimeofday(&endTime, NULL);
        result.runningTime.tv_sec = endTime.tv_sec - startTime.tv_sec;
        if((endTime.tv_usec - startTime.tv_usec) < 0)
        {
            result.runningTime.tv_sec--;
            result.runningTime.tv_usec = (startTime.tv_usec - endTime.tv_usec) + 1;
        }
        else
        {
            result.runningTime.tv_usec = endTime.tv_usec - startTime.tv_usec;
        }
    }

    return done;
}

void EvolutionManager::Step()
{
    // Nastartovani casovace (pokud jde o prvni generaci)
    if(actGeneration == 0)
        gettimeofday(&startTime, NULL);

    childPop.clear();
    tempPop.clear();

    sort(parentPop.begin(), parentPop.end(), FitnessSort);  // serazeni dle ohodnoceni
    Crossover(parentPop, Config::GetInstance()->pSelectReproduct, Config::GetInstance()->pSelectDelete);  // aplikace krizeni
    Mutation(parentPop, Config::GetInstance()->sElitism);   // aplikace mutace
    EvaluatePopulation(parentPop);

    this->actGeneration++;
}

void EvolutionManager::Crossover(vector<tIndividual> &population, float pSelectReproduct, float pSelectDelete)
{
    int bestCount = floor(population.size() * pSelectReproduct + 0.5);
    int worstCount = floor(population.size() * pSelectDelete + 0.5);
    int worstIndex = population.size() - worstCount;

    int randomParent1, randomParent2, randomPoint1, randomPoint2;
    tIndividual child1, child2;
    child1.price = 0;
    child2.price = 0;

    // Mala pomucka - nejlepsi jedinec je vzdy jeste jednou zkopirovan do populace, aby se zvysila moznost jeho mutace
    child1 = population[0];
    child1.iteration = 1;
    parentPop[worstIndex++] = child1;

    // Generovani potomku pomoci krizeni
    while(true)
    {
        randomParent1 = rand() % bestCount;
        randomParent2 = rand() % bestCount;
        randomPoint1 = rand() % parentPop[randomParent1].rule.size();
        randomPoint2 = rand() % parentPop[randomParent2].rule.size();

        child1.iteration = parentPop[randomParent1].iteration;
        child2.iteration = parentPop[randomParent2].iteration;

        child1.rule = "";
        child2.rule = "";

        // Vytvoreni prvniho potomka
        for(int i = 0; i < randomPoint1; i++)
            child1.rule += parentPop[randomParent1].rule[i];
        for(int i = randomPoint2; i < (int)parentPop[randomParent2].rule.size(); i++)
            child1.rule += parentPop[randomParent2].rule[i];
        parentPop[worstIndex++] = child1;
        if(worstIndex == (int)parentPop.size())
            break;

        // Vytvoreni druheho potomka
        for(int i = 0; i < randomPoint2; i++)
            child2.rule += parentPop[randomParent2].rule[i];
        for(int i = randomPoint1; i < (int)parentPop[randomParent1].rule.size(); i++)
            child2.rule += parentPop[randomParent1].rule[i];
        parentPop[worstIndex++] = child2;
        if(worstIndex == (int)parentPop.size())
            break;

        this->result.crossoverCount++;
    }
}

void EvolutionManager::Mutation(vector<tIndividual> &population, int sElitism)
{
    float randomValue;

    // Aplikace mutace na vsechny jedince populace s vyjimkou tech, na ktere se vztahuje parametr elitismu
    for(int i = sElitism; i < (int)population.size(); i++)
    {
        // Obycejna mutace (zamena hodnoty kodonu) je s urcitou pravdepodobnosti aplikovana na kazdy kodon
        for(int j = 0; j < (int)population[i].rule.size(); j++)
        {
            randomValue = (float)rand() / RAND_MAX;
            if(randomValue < Config::GetInstance()->pMutation)
            {
                population[i].rule[j] = rand() % CHAR_MAX;
                result.mutationCount++;
            }
        }

        // Inserce kodonu je vypocitavana pro cely genom a muze v jednom kroku probehnout pouze jedenkrat
        randomValue = (float)rand() / RAND_MAX;
        if(randomValue < Config::GetInstance()->pInsertion)
        {
            population[i].rule.insert(rand() % population[i].rule.size(), 1, (rand() % CHAR_MAX));
            result.insertionCount++;
        }

        // Delece kodonu je vypocitavana pro cely genom a muze v jednom kroku probehnout pouze jedenkrat
        randomValue = (float)rand() / RAND_MAX;
        if(randomValue < Config::GetInstance()->pDeletion)
        {
            population[i].rule.erase(population[i].rule.begin() + (rand() % population[i].rule.size()));
            result.deletionCount++;
        }

        // Mutace poctu iteraci
        randomValue = (float)rand() / RAND_MAX;
        if(randomValue < Config::GetInstance()->pMutationIteration)
            population[i].iteration = rand() % Config::GetInstance()->iterationMax + 1;
    }
}

void EvolutionManager::SetGenerationStatistics()
{
    result.minCurrentImagePrice = INT_MAX;
    result.maxCurrentImagePrice = 0;
    result.avgCurrentImagePrice = 0;

    for(int i = 0; i < (int)parentPop.size(); i++)
    {
        if(parentPop[i].price > result.maxCurrentImagePrice)
            result.maxCurrentImagePrice = parentPop[i].price;
        if(parentPop[i].price > result.maxImagePrice)
            result.maxImagePrice = parentPop[i].price;
        if(parentPop[i].price < result.minCurrentImagePrice)
            result.minCurrentImagePrice = parentPop[i].price;
        if(parentPop[i].price < result.minImagePrice)
        {
            result.minImagePrice = parentPop[i].price;
            resultIndividual = parentPop[i];
        }
        result.avgCurrentImagePrice += parentPop[i].price;
    }
    result.avgCurrentImagePrice = result.avgCurrentImagePrice / parentPop.size();
    tempAvgImagePrice.push_back(result.avgCurrentImagePrice);
    tempMinImagePrice.push_back(result.minCurrentImagePrice);
    tempMaxImagePrice.push_back(result.maxCurrentImagePrice);
}

void EvolutionManager::StopEvolution()
{
    if(sleepFlag)
    {   // Obnoveni prehravani
        mutex.lock();
        sleepFlag = false;
        condition.wakeOne();
        mutex.unlock();
    }
    else
    {   // Pozastaveni prehravani
        mutex.lock();
        sleepFlag = true;
        mutex.unlock();
    }
}

void EvolutionManager::AbortEvolution()
{
    mutex.lock();
    abortFlag = true;      // Nastaveni priznaku pro ukonceni
    condition.wakeOne();   // Probuzeni spiciho vlakna
    mutex.unlock();

    wait();                // Pockani na dobehnuti vlakna
}

bool EvolutionManager::SaveResults(string outputFile)
{
    ofstream file;
    file.open(outputFile.c_str());

    if(!file.good())
        return false;

    // Vypocet prumerne ceny za vsechny generace
    float multConstant = (float)1 / ((float)actGeneration / Config::GetInstance()->logInterval);
    for(int i = 0; i < (int)tempAvgImagePrice.size(); i++)
        result.avgImagePrice += tempAvgImagePrice[i] * multConstant;

    file << "***** NALEZENA GRAMATIKA *****\n";
    file << "Angle: " << std::fixed << std::setprecision(1) << (Config::GetInstance()->initAngle * 180 / M_PI) << "\n";
    file << "Axiom: " << Config::GetInstance()->initAxiom << "\n";
    file << "Pravidlo: F -> " << resultIndividual.transcriptRule << "\n";
    file << "Pocet iteraci: " << resultIndividual.iteration << "\n\n";

    file << "***** PARAMETRY BEHU GA *****\n";
    file << Config::GetInstance()->problemFile      << "\t # cesta k vstupnimu souboru - hledanemu obrazku\n";
    file << actGeneration                           << "\t # aktualni generace behu vypoctu\n";
    file << Config::GetInstance()->sPopulation      << "\t # velikost populace\n";
    file << Config::GetInstance()->initIteration    << "\t # pocatecni pocet iteraci\n";
    file << Config::GetInstance()->iterationMax     << "\t # maximalni pocet iteraci\n";
    file << Config::GetInstance()->ruleLength       << "\t # pocet integeru, z kterych bude sestaven pocatecni konstrukcni vektor.\n";
    file << std::fixed << std::setprecision(1)      << (Config::GetInstance()->initAngle * 180 / M_PI) << "\t # pocatecni uhel\n";
    file << Config::GetInstance()->initAxiom        << "\t # pocatecni axiom\n";
    file << Config::GetInstance()->sElitism         << "\t # elitismus\n";
    file << result.crossoverCount        << "\t # pocet aplikaci operatoru krizeni od inicializace\n";
    file << result.mutationCount         << "\t # pocet aplikaci operatoru obycejne mutace od inicializace\n";
    file << result.insertionCount        << "\t # pocet aplikaci operatoru mutace - inserce od inicializace\n";
    file << result.deletionCount         << "\t # pocet aplikaci operatoru mutace - delece od inicializace\n";
    file << result.genomeEvaluationCount << "\t # pocet ohodnoceni genomu od inicializace\n\n";

    file << "***** CELKOVE STATISTIKY *****\n";
    file << result.runningTime.tv_sec << "." << result.runningTime.tv_usec << "s\t # doba behu vypoctu\n";
    file << result.minImagePrice          << "\t # nejlepsi cena od inicializace\n";
    file << result.maxImagePrice          << "\t # nejhorsi cena od inicializace\n";
    file << result.avgImagePrice          << "\t # prumerna cena od inicializace\n\n";

    file << "***** STATISTIKY K POCATECNI POPULACI *****\n";
    file << result.minInitialImagePrice   << "\t # nejlepsi cena v pocatecni populaci\n";
    file << result.maxInitialImagePrice   << "\t # nejhorsi cena v pocatecni populaci\n";
    file << result.avgInitialImagePrice   << "\t # prumerna cena v pocatecni populaci\n\n";

    file << "***** STATISTIKY K AKTUALNI POPULACI *****\n";
    file << result.minCurrentImagePrice   << "\t # nejlepsi cena v aktualni populaci\n";
    file << result.maxCurrentImagePrice   << "\t # nejhorsi cena v aktualni populaci\n";
    file << result.avgCurrentImagePrice   << "\t # prumerna cena v aktualni populaci\n\n";

    file << "***** MEZIVYSLEDKY *****\n";
    for(int i = 0; i < (int)tempMinImagePrice.size(); i++)
    {
        file << (i * Config::GetInstance()->logInterval) << " \t";
        file << tempMinImagePrice[i] << " \t";
        file << tempAvgImagePrice[i] << " \t";
        file << tempMaxImagePrice[i] << "\n";
    }

    file.close();

    return true;
}

bool FitnessSort(tIndividual inv1, tIndividual inv2)
{
    return (inv1.price < inv2.price);
}
