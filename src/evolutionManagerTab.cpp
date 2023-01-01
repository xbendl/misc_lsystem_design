#include "evolutionManagerTab.h"

using namespace std;

EvolutionManagerTab::EvolutionManagerTab(QWidget *parent) : QWidget(parent)
{
    // Ziskani zadanych parametru z prikazoveho radku
    QStringList arguments = QCoreApplication::arguments();

    QLabel *evolutionParameterLabel = new QLabel(tr("Parametry evoluce:"), this);
    evolutionParameterLabel->setFont(QFont("Helvetica", 12, QFont::Bold));
    evolutionParameterLabel->move(10, 10);
    QLabel *taskChooseLabel = new QLabel(tr("Uloha"), this);
    taskChooseLabel->move(10, 45);
    QLabel *sPopulationLabel = new QLabel(tr("Velikost populace"), this);
    sPopulationLabel->move(10, 75);
    QLabel *nGenerationsLabel = new QLabel(tr("Pocet generaci"), this);
    nGenerationsLabel->setGeometry(10, 101, 200, 23);
    QLabel *pMutationLabel = new QLabel(tr("Pravdepodobnost mutace"), this);
    pMutationLabel->setToolTip("Pravdepodobnost mutace - v ramci mutace se s urcenou pravdepodobnosti provadi bud zamena / pridani / vypusteni kodonu.");
    pMutationLabel->move(10, 135);
    pMutationLabel->setCursor(Qt::WhatsThisCursor);
    QLabel *pInsertionLabel = new QLabel(tr("Pravdepodobnost inserce"), this);
    pInsertionLabel->setToolTip("Pravdepodobnost inserce pri aplikaci operatoru mutace. Zpusobi pridani nahodne vygenerovaneho kodonu na nahodne urcene misto.");
    pInsertionLabel->move(10, 165);
    pInsertionLabel->setCursor(Qt::WhatsThisCursor);
    QLabel *pDeletionLabel = new QLabel(tr("Pravdepodobnost delece"), this);
    pDeletionLabel->setToolTip("Pravdepodobnost delece pri aplikaci operatoru mutace. Zpusobi smazani nahodne vybraneho kodonu.");
    pDeletionLabel->move(10, 195);
    pDeletionLabel->setCursor(Qt::WhatsThisCursor);
    QLabel *pSelectReproduct = new QLabel(tr("Vyber pro reprodukci"), this);
    pSelectReproduct->move(10, 225);
    pSelectReproduct->setToolTip("Pocet nejlepe ohodnocenych jedincu ucastnicich se procesu krizeni.");
    pSelectReproduct->setCursor(Qt::WhatsThisCursor);
    QLabel *sElitismLabel = new QLabel(tr("Elitismus"), this);
    sElitismLabel->move(10, 255);
    sElitismLabel->setToolTip("Pocet nejlepe ohodnocenych jedincu populace, ktere automaticky prechazeji do dalsi generace.");
    sElitismLabel->setCursor(Qt::WhatsThisCursor);
    QLabel *logIntervalLabel = new QLabel(tr("Interval logu"), this);
    logIntervalLabel->move(10, 285);
    logIntervalLabel->setToolTip("Pocet generaci, po kterych dojde k zaznamenani aktualnich statistik.");
    logIntervalLabel->setCursor(Qt::WhatsThisCursor);

    loadTaskButton = new QPushButton(tr("Vybrat ulohu"), this);
    loadTaskButton->setGeometry(145, 40, 180, 25);
    sPopulationStepLine = new QSpinBox(this);
    sPopulationStepLine->setRange(1, (INT_MAX - 1));
    sPopulationStepLine->setGeometry(215, 70, 110, 25);
    nGenerationsStepLine = new QSpinBox(this);
    nGenerationsStepLine->setRange(1, (INT_MAX - 1));
    nGenerationsStepLine->setGeometry(215, 100, 110, 25);
    pMutationDoubleSpinBox = new QDoubleSpinBox(this);
    pMutationDoubleSpinBox->setRange(0, 1);
    pMutationDoubleSpinBox->setDecimals(3);
    pMutationDoubleSpinBox->setSingleStep(0.001);
    pMutationDoubleSpinBox->setGeometry(215, 130, 110, 25);
    pInsertionDoubleSpinBox = new QDoubleSpinBox(this);
    pInsertionDoubleSpinBox->setRange(0, 1);
    pInsertionDoubleSpinBox->setDecimals(3);
    pInsertionDoubleSpinBox->setSingleStep(0.001);
    pInsertionDoubleSpinBox->setGeometry(215, 160, 110, 25);
    pDeletionDoubleSpinBox = new QDoubleSpinBox(this);
    pDeletionDoubleSpinBox->setRange(0, 1);
    pDeletionDoubleSpinBox->setDecimals(3);
    pDeletionDoubleSpinBox->setSingleStep(0.001);
    pDeletionDoubleSpinBox->setGeometry(215, 190, 110, 25);
    pSelectReproductDoubleSpinBox = new QDoubleSpinBox(this);
    pSelectReproductDoubleSpinBox->setRange(0, 1);
    pSelectReproductDoubleSpinBox->setDecimals(3);
    pSelectReproductDoubleSpinBox->setSingleStep(0.001);
    pSelectReproductDoubleSpinBox->setGeometry(215, 220, 110, 25);
    sElitismStepLine = new QSpinBox(this);
    sElitismStepLine->setRange(0, (INT_MAX - 1));
    sElitismStepLine->setGeometry(215, 250, 110, 25);
    logIntervalStepLine = new QSpinBox(this);
    logIntervalStepLine->setRange(1, (INT_MAX - 1));
    logIntervalStepLine->setGeometry(215, 280, 110, 25);

    evoluteStartButton = new QPushButton(tr("Start"), this);
    evoluteStartButton->setGeometry(10, 312, 73, 25);
    evoluteStartButton->setEnabled(false);
    evoluteStopButton = new QPushButton(tr("Pozastavit"), this);
    evoluteStopButton->setGeometry(88, 312, 73, 25);
    evoluteStopButton->setEnabled(false);
    evoluteAbortButton = new QPushButton(tr("Zrusit"), this);
    evoluteAbortButton->setGeometry(166, 312, 74, 25);
    evoluteAbortButton->setEnabled(false);
    saveResultButton = new QPushButton(tr("Ulozit"), this);
    saveResultButton->setGeometry(245, 312, 80, 25);
    saveResultButton->setEnabled(false);

    // Sekce "Graficke reseni"
    QLabel *graphicPatternLabel = new QLabel(tr("Predloha:"), this);
    graphicPatternLabel->setFont(QFont("Helvetica", 12, QFont::Bold));
    graphicPatternLabel->move(360, 10);
    QLabel *graphicSolutionLabel = new QLabel(tr("Kandidatni reseni:"), this);
    graphicSolutionLabel->setFont(QFont("Helvetica", 12, QFont::Bold));
    graphicSolutionLabel->move(638, 10);
    evolutionProgressBar = new QProgressBar(this);
    evolutionProgressBar->setGeometry(355, 313, 542, 25);
    evolutionProgressBar->setMinimum(0);
    evolutionProgressBar->setTextVisible(false);
    QLabel *projectStatus = new QLabel(tr("Prubeh evoluce pravidel"), this);
    projectStatus->setStyleSheet("font-weight: bold");
    projectStatus->setGeometry(520, 318, 300, 18);
    resultTextBox = new QPlainTextEdit(this);
    resultTextBox->setGeometry(10, 345, 888, 80);
    resultTextBox->setFont(QFont("Courier New", 8, QFont::Normal));
    resultTextBox->setReadOnly(true);
    patternWidget = new TurtleWidget(this);
    patternWidget->setGeometry(355, 40, Config::GetInstance()->imageSizeRect, Config::GetInstance()->imageSizeRect);
    solutionWidget = new TurtleWidget(this);
    solutionWidget->setGeometry(633, 40, Config::GetInstance()->imageSizeRect, Config::GetInstance()->imageSizeRect);

    // Nastaveni slotu a signalu
    connect(loadTaskButton, SIGNAL(clicked()), this, SLOT(SetOpenFileName()));
    connect(evoluteStartButton, SIGNAL(clicked()), this, SLOT(StartEvolution()));
    connect(evoluteStopButton, SIGNAL(clicked()), this, SLOT(StopEvolution()));
    connect(evoluteAbortButton, SIGNAL(clicked()), this, SLOT(AbortEvolution()));
    connect(saveResultButton, SIGNAL(clicked()), this, SLOT(SetResultFile()));
    connect(sPopulationStepLine, SIGNAL(valueChanged(int)), this, SLOT(ChangeSPopulation(int)));
    connect(nGenerationsStepLine, SIGNAL(valueChanged(int)), this, SLOT(ChangeNGenerations(int)));
    connect(pMutationDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ChangePMutation(double)));
    connect(pInsertionDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ChangePInsertion(double)));
    connect(pDeletionDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ChangePDeletion(double)));
    connect(pSelectReproductDoubleSpinBox, SIGNAL(valueChanged(double)), this, SLOT(ChangePSelectReproduct(double)));
    connect(sElitismStepLine, SIGNAL(valueChanged(int)), this, SLOT(ChangeSElitism(int)));
    connect(logIntervalStepLine, SIGNAL(valueChanged(int)), this, SLOT(ChangeLogInterval(int)));
    connect(logIntervalStepLine, SIGNAL(valueChanged(int)), this, SLOT(ChangeLogInterval(int)));
    connect(&evolutionManager, SIGNAL(CurrentImageGenerated(QImage, tIndividual, int, int, int, int)), this, SLOT(ReceiveCurrentImageGenerated(QImage, tIndividual, int, int, int, int)));
    connect(&evolutionManager, SIGNAL(ImageGenerated(QImage, tIndividual)), this, SLOT(ReceiveImageGenerated(QImage, tIndividual)));

    // Zpracovani parametru prikazove radky
    if(arguments.size() == 2)
    {
        // Nacteni udaju z konfiguracniho souboru
        string configFile = arguments[1].toStdString();
        Config::GetInstance()->LoadConfiguration(configFile);

        // Nacteni hledaneho obrazku
        QString inputFile = QString(Config::GetInstance()->problemFile.c_str());
        if(inputFile.startsWith(QApplication::applicationDirPath(), Qt::CaseSensitive))
        {   // Zmena absolutni cesty na relativni
            inputFile = inputFile.right(inputFile.size() - QApplication::applicationDirPath().size() - 1);
        }

        // Nastaveni ovladacich prvku
        evolutionProgressBar->setValue(evolutionProgressBar->minimum());
        evoluteStartButton->setEnabled(true);
        evoluteStopButton->setText("Pozastavit");

        // Uprava obrazku a jeho umisteni do widgetu
        QImage dummyImage(inputFile);
        pattern = dummyImage;
        QImage scaledImage;
        TurtleGraphic::ScaleImage(pattern, scaledImage, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);      // Zmenseni obrazku na rozmery widgetu v okne
        patternWidget->SetImage(scaledImage);
    }

    // Nastaveni hodnot ovladacich prvku
    sPopulationStepLine->setValue(Config::GetInstance()->sPopulation);
    nGenerationsStepLine->setValue(Config::GetInstance()->nGenerations);
    sElitismStepLine->setValue(Config::GetInstance()->sElitism);
    logIntervalStepLine->setValue(Config::GetInstance()->logInterval);
    pMutationDoubleSpinBox->setValue(Config::GetInstance()->pMutation);
    pInsertionDoubleSpinBox->setValue(Config::GetInstance()->pInsertion);
    pDeletionDoubleSpinBox->setValue(Config::GetInstance()->pDeletion);
    pSelectReproductDoubleSpinBox->setValue(Config::GetInstance()->pSelectReproduct);
}

void EvolutionManagerTab::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(340, 40, 340, 335);
}

void EvolutionManagerTab::SetOpenFileName()
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Vyberte ulohu"), "", tr("BMP soubory (*.bmp)"));

    if(!inputFile.isEmpty())
    {
        if(inputFile.startsWith(QApplication::applicationDirPath(), Qt::CaseSensitive))
        {   // Zmena absolutni cesty na relativni
            inputFile = inputFile.right(inputFile.size() - QApplication::applicationDirPath().size() - 1);
        }

        Config::GetInstance()->problemFile = inputFile.toStdString();
        resultTextBox->clear();
        solutionWidget->ClearWidget();

        // Vypsani nazvu reseneho problemu (nazvu souboru)
        QString headerText = QString("<strong><u>Uloha: ") + QString(inputFile) + QString("<u></strong><br />");
        resultTextBox->appendHtml(headerText);

        // Nastaveni ovladacich prvku
        evolutionProgressBar->setValue(evolutionProgressBar->minimum());
        evoluteStartButton->setEnabled(true);
        evoluteStopButton->setText("Pozastavit");

        // Nacteni obrazku a jeho umisteni do widgetu
        QImage dummyImage(inputFile);
        pattern = dummyImage;
        QImage scaledImage;
        TurtleGraphic::ScaleImage(pattern, scaledImage, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);      // Zmenseni obrazku na rozmery widgetu v okne
        patternWidget->SetImage(scaledImage);

        update();
    }
}

void EvolutionManagerTab::SetResultFile()
{
    QFileDialog *saveDialog = new QFileDialog();
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveDialog->setDefaultSuffix("txt");

    if(saveDialog->exec())
        if((saveDialog->selectedFiles()).size() > 0)
            if(!(evolutionManager.SaveResults(((saveDialog->selectedFiles())[0]).toStdString())))
            {
                QMessageBox *error = new QMessageBox(QMessageBox::Critical, tr("Chyba"), tr("Ulozeni vysledku do vystupniho souboru se nezdarilo.\nMozne priciny: Evoluce nebyla dokoncena."), QMessageBox::Ok, this, Qt::Widget);
                error->show();
            }
}

void EvolutionManagerTab::StartEvolution()
{
    // Odemknuti / zamknuti ovladacich prvku
    loadTaskButton->setEnabled(false);
    evoluteStartButton->setEnabled(false);
    evoluteStopButton->setEnabled(true);
    evoluteAbortButton->setEnabled(true);
    saveResultButton->setEnabled(false);
    sPopulationStepLine->setEnabled(false);
    nGenerationsStepLine->setEnabled(false);
    sElitismStepLine->setEnabled(false);
    logIntervalStepLine->setEnabled(false);
    pMutationDoubleSpinBox->setEnabled(false);
    pInsertionDoubleSpinBox->setEnabled(false);
    pDeletionDoubleSpinBox->setEnabled(false);
    pSelectReproductDoubleSpinBox->setEnabled(false);

    // Nastaveni progressBaru
    evolutionProgressBar->setValue(evolutionProgressBar->minimum());
    evolutionProgressBar->setMaximum(Config::GetInstance()->nGenerations);

    // Spusteni evoluce
    evolutionManager.FindSolution(pattern);

    // Vypsani nazvu reseneho problemu (nazvu souboru) a zahlavi
    resultTextBox->clear();
    QString headerText = QString("<strong><u>Uloha: ") + QString(Config::GetInstance()->problemFile.c_str()) + QString("<u></strong><br />");
    resultTextBox->appendHtml(headerText);
    resultTextBox->appendHtml(QString("<strong>Generace&nbsp;&nbsp;Min&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Avg&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Max"));
}

void EvolutionManagerTab::StopEvolution()
{
    if(evoluteStopButton->text() == "Pozastavit")   // Stridani textu na buttonu Pozastavit / Obnovit
        evoluteStopButton->setText("Obnovit");
    else if(evoluteStopButton->text() == "Obnovit")
        evoluteStopButton->setText("Pozastavit");

    evolutionManager.StopEvolution();    // Pokyn k pozastaveni evoluce
}

void EvolutionManagerTab::AbortEvolution()
{
    evolutionManager.AbortEvolution();   // Pokyn k zastaveni evoluce

    // Vypis vysledku nejlepsiho jedince
    stringstream out1, out2;
    out1 << Config::GetInstance()->initIteration;
    string iteration = out1.str();
    out2 << resultIndividual.price;
    string price = out2.str();

    resultTextBox->appendHtml(QString("<strong>______________________________________</strong>"));
    QString priceText = QString("<strong>Cena: </strong>&nbsp;&nbsp;&nbsp;&nbsp;") + QString(price.c_str());
    QString axiomText = QString("<strong>Axiom: </strong>&nbsp;&nbsp;&nbsp;") + QString(Config::GetInstance()->initAxiom.c_str());
    QString iterationText = QString("<strong>Iterace: </strong>&nbsp;") + QString(iteration.c_str());
    QString ruleText = QString("<strong>Pravidlo: </strong>") + QString(resultIndividual.transcriptRule.c_str());
    resultTextBox->appendHtml(priceText);
    resultTextBox->appendHtml(axiomText);
    resultTextBox->appendHtml(iterationText);
    resultTextBox->appendHtml(ruleText);

    // Odemknuti / zamknuti ovladacich prvku
    loadTaskButton->setEnabled(true);
    evoluteStartButton->setEnabled(true);
    evoluteStopButton->setEnabled(false);
    evoluteAbortButton->setEnabled(false);
    saveResultButton->setEnabled(true);
    evoluteStopButton->setText(QString("Pozastavit"));
    sPopulationStepLine->setEnabled(true);
    nGenerationsStepLine->setEnabled(true);
    sElitismStepLine->setEnabled(true);
    logIntervalStepLine->setEnabled(true);
    pMutationDoubleSpinBox->setEnabled(true);
    pInsertionDoubleSpinBox->setEnabled(true);
    pDeletionDoubleSpinBox->setEnabled(true);
    pSelectReproductDoubleSpinBox->setEnabled(true);
}

string EvolutionManagerTab::GetAlignString(int number, int spaceCount)
{
    int digitCount = 0;

    int dummyNumber = number;
    do
    {
        dummyNumber /= 10;
        digitCount++;
    }
    while(dummyNumber >= 1);

    stringstream out;
    out << number;
    string output = out.str();

    for(int i = 0; i < (spaceCount - digitCount); i++)
        output += "&nbsp;";

    return output;
}

void EvolutionManagerTab::ChangeSPopulation(int newValue)
{
    Config::GetInstance()->sPopulation = newValue;
}

void EvolutionManagerTab::ChangeNGenerations(int newValue)
{
    Config::GetInstance()->nGenerations = newValue;
}

void EvolutionManagerTab::ChangePMutation(double newValue)
{
    Config::GetInstance()->pMutation = newValue;
}

void EvolutionManagerTab::ChangePInsertion(double newValue)
{
    Config::GetInstance()->pInsertion = newValue;
}

void EvolutionManagerTab::ChangePDeletion(double newValue)
{
    Config::GetInstance()->pDeletion = newValue;
}

void EvolutionManagerTab::ChangePSelectReproduct(double newValue)
{
    Config::GetInstance()->pSelectReproduct = newValue;
}

void EvolutionManagerTab::ChangeSElitism(int newValue)
{
    Config::GetInstance()->sElitism = newValue;
}

void EvolutionManagerTab::ChangeLogInterval(int newValue)
{
    Config::GetInstance()->logInterval = newValue;
}

void EvolutionManagerTab::ReceiveCurrentImageGenerated(QImage resultImage, tIndividual resultIndividual, int actGeneration, int minCurrentImagePrice, int avgCurrentImagePrice, int maxCurrentImagePrice)
{
    this->resultIndividual = resultIndividual;

    // Vykresleni obrazku na widgetu v okne
    solutionWidget->SetImage(resultImage);

    // Vypis mezivysledku (minimalni, prumerna a maximalni cena v ramci dane generace) do textoveho pole pro vysledky
    string row = GetAlignString(actGeneration, 10);
    row += GetAlignString(minCurrentImagePrice, 10);
    row += GetAlignString(avgCurrentImagePrice, 10);
    row += GetAlignString(maxCurrentImagePrice, 10);

    QString qRow(row.c_str());
    resultTextBox->appendHtml(qRow);

    evolutionProgressBar->setValue(actGeneration);
}

void EvolutionManagerTab::ReceiveImageGenerated(QImage resultImage, tIndividual resultIndividual)
{
    this->resultIndividual = resultIndividual;

    // Vykresleni obrazku na widgetu v okne
    solutionWidget->SetImage(resultImage);

    // Vypis vysledku nejlepsiho jedince
    stringstream out1, out2;
    out1 << Config::GetInstance()->initIteration;
    string iteration = out1.str();
    out2 << resultIndividual.price;
    string price = out2.str();

    resultTextBox->appendHtml(QString("<strong>______________________________________</strong>"));
    QString priceText = QString("<strong>Cena: </strong>&nbsp;&nbsp;&nbsp;&nbsp;") + QString(price.c_str());
    QString axiomText = QString("<strong>Axiom: </strong>&nbsp;&nbsp;&nbsp;") + QString(Config::GetInstance()->initAxiom.c_str());
    QString iterationText = QString("<strong>Iterace: </strong>&nbsp;") + QString(iteration.c_str());
    QString ruleText = QString("<strong>Pravidlo: </strong>") + QString(resultIndividual.transcriptRule.c_str());
    resultTextBox->appendHtml(priceText);
    resultTextBox->appendHtml(axiomText);
    resultTextBox->appendHtml(iterationText);
    resultTextBox->appendHtml(ruleText);

    // Odemknuti / zamknuti ovladacich prvku
    loadTaskButton->setEnabled(true);
    evoluteStartButton->setEnabled(true);
    evoluteStopButton->setEnabled(false);
    evoluteAbortButton->setEnabled(false);
    saveResultButton->setEnabled(true);
    evoluteStopButton->setText(QString("Pozastavit"));
    sPopulationStepLine->setEnabled(true);
    nGenerationsStepLine->setEnabled(true);
    sElitismStepLine->setEnabled(true);
    logIntervalStepLine->setEnabled(true);
    pMutationDoubleSpinBox->setEnabled(true);
    pInsertionDoubleSpinBox->setEnabled(true);
    pDeletionDoubleSpinBox->setEnabled(true);
    pSelectReproductDoubleSpinBox->setEnabled(true);
}
