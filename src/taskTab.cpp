#include "taskTab.h"

using namespace std;

TaskTab::TaskTab(QWidget *parent) : QWidget(parent)
{
    QLabel *createNewTaskLabel = new QLabel(tr("Vytvoreni nove ulohy:"), this);
    createNewTaskLabel->setFont(QFont("Helvetica", 12, QFont::Bold));
    createNewTaskLabel->move(10, 10);
    QLabel *taskChooseLabel = new QLabel(tr("Podle obrazku"), this);
    taskChooseLabel->move(10, 45);
    QLabel *taskIterationLabel = new QLabel(tr("Pocet iteraci"), this);
    taskIterationLabel->move(10, 255);

    loadTaskButton = new QPushButton(tr("Vybrat ulohu"), this);
    loadTaskButton->setGeometry(145, 40, 180, 25);
    taskRulesTextBox = new QPlainTextEdit(this);
    taskRulesTextBox->setGeometry(10, 70, 315, 175);
    taskRulesTextBox->setFont(QFont("Courier New", 8, QFont::Normal));
    taskIteration = new QSpinBox(this);
    taskIteration->setRange(0, (INT_MAX - 1));
    taskIteration->setGeometry(145, 250, 180, 25);
    taskIteration->setValue(1);
    createNewTaskButton = new QPushButton(tr("Vytvorit nahled"), this);
    createNewTaskButton->setGeometry(10, 280, 130, 25);
    saveNewTaskButton = new QPushButton(tr("Ulozit ulohu"), this);
    saveNewTaskButton->setGeometry(145, 280, 180, 25);

    // Sekce "Nahled"
    QLabel *graphicSolutionLabel = new QLabel(tr("Nahled:"), this);
    graphicSolutionLabel->setFont(QFont("Helvetica", 12, QFont::Bold));
    graphicSolutionLabel->move(360, 10);
    taskViewWidget = new TurtleWidget(this);
    taskViewWidget->setGeometry(355, 40, Config::GetInstance()->imageSizeRect, Config::GetInstance()->imageSizeRect);
    resultTextBox= new QPlainTextEdit(this);
    resultTextBox->setGeometry(10, 315, 888, 110);
    resultTextBox->setFont(QFont("Courier New", 8, QFont::Normal));
    resultTextBox->setReadOnly(true);

    pattern = new QImage(Config::GetInstance()->imageSize, Config::GetInstance()->imageSize, QImage::Format_Mono);

    // Nastaveni slotu a signalu
    connect(loadTaskButton, SIGNAL(clicked()), this, SLOT(SetOpenFileName()));
    connect(createNewTaskButton, SIGNAL(clicked()), this, SLOT(CreateNewTaskByRules()));
    connect(saveNewTaskButton, SIGNAL(clicked()), this, SLOT(SaveNewTask()));
    connect(taskIteration, SIGNAL(valueChanged(int)), this, SLOT(ChangeCIteration(int)));
}

TaskTab::~TaskTab()
{
    delete pattern;
}

void TaskTab::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(QPen(Qt::gray, 1));
    painter.drawLine(340, 40, 340, 305);
}

void TaskTab::CreateNewTaskByRules()
{
    vector<tExtendedRule> rules;
    resultTextBox->clear();

    // Nahrazeni sipky ve vstupu za # a rozsekani na jednotlive radky
    QString inputQString = taskRulesTextBox->toPlainText();
    QStringList inputLine = inputQString.split(QString("\n"), QString::KeepEmptyParts, Qt::CaseInsensitive);
    string line, paramValue, leftSide, rightSide;
    unsigned int cutAt;

    // Rozpoznavani jednotlivych radku
    //float step = 100;     // nahodne nastavena nejaka magicka hodnota (bude prepocitana podle potreby)
    float angle = 0;
    string axiom;

    for(int i = 0; i < inputLine.size(); i++)
    {
        string line = inputLine[i].toStdString();

        if((cutAt = line.find("axiom")) != line.npos)
        {   // ziskani axiomu l-systemu
            paramValue = line.substr(line.find("=") + 1);
            StringTrim(paramValue);
            axiom = paramValue;
        }
        else if((cutAt = line.find("alpha")) != line.npos)
        {   // ziskani uhlu l-systemu
            paramValue = line.substr(line.find("=") + 1);
            StringTrim(paramValue);
            angle = atof(paramValue.c_str());
            angle = angle * M_PI / 180;
        }
        else if((cutAt = line.find("=")) != line.npos)
        {   // ziskani pravidel l-systemu
            tExtendedRule actRule;

            leftSide = line.substr(0, cutAt);
            StringTrim(leftSide);
            actRule.symbol = leftSide[0];

            rightSide = line.substr(cutAt + 1);
            StringTrim(rightSide);
            actRule.rightSide = rightSide;

            rules.push_back(actRule);
        }
    }

    // Aplikace pravidel pro vytvoreni vysledneho retezce
    string newAxiom = "";
    string actAxiom = axiom;
    bool found;
    for(int i = 0; i < (int) Config::GetInstance()->cIteration; i++)
    {
        for(int j = 0; j < (int)actAxiom.size(); j++)
        {
            found = false;
            for(int k = 0; k < (int)rules.size(); k++)
            {
                if(actAxiom[j] == rules[k].symbol)
                {
                    newAxiom += rules[k].rightSide;
                    found = true;
                    break;
                }
            }
            if(!found)
                newAxiom += actAxiom[j];
        }
        actAxiom = newAxiom;
        newAxiom = "";
    }

    // Vypis vygenerovaneho retezce do pole pro vysledky
    stringstream out;
    out << actAxiom.size();
    string resultText = "<strong><u>Vygenerovany retezec</u></strong> (Delka retezce:" + out.str() + ")<br />" + actAxiom + "<br />";
    QString qResultText(resultText.c_str());
    resultTextBox->appendHtml(qResultText);

    // Vykresleni obrazce podle vygenerovaneho retezce
    QImage viewImage = TurtleGraphic::CreateImage(actAxiom, angle);
    taskViewWidget->SetImage(viewImage);
    *pattern = viewImage;
}

void TaskTab::ChangeCIteration(int newValue)
{
    Config::GetInstance()->cIteration = newValue;
}

void TaskTab::SetOpenFileName()
{
    QString inputFile = QFileDialog::getOpenFileName(this, tr("Vyberte soubor s ulohou"), "", tr("Vsechny soubory (*)"));

    if(!inputFile.isEmpty() > 0)
    {
        if(inputFile.startsWith(QApplication::applicationDirPath(), Qt::CaseSensitive))
        {   // Zmena absolutni cesty na relativni
            inputFile = inputFile.right(inputFile.size() - QApplication::applicationDirPath().size() - 1);
        }
        taskRulesTextBox->clear();
        resultTextBox->clear();

        // Nacteni a uprava obrazku
        QImage scaledImage, croppedImage;
        QImage loadedImage(inputFile);
        TurtleGraphic::CropImage(loadedImage, croppedImage);
        TurtleGraphic::ScaleImage(croppedImage, scaledImage, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);      // Zmenseni obrazku na rozmery widgetu v okne

        // Vykresleni obrazku na widgetu v okne
        taskViewWidget->SetImage(scaledImage);

        // Priprava obrazku pro ulozeni (tj. nastaveni aby byl vycentrovany v platne pozadovaneho ctvercoveho rozmeru)
        QPainter painter(pattern);
        painter.setPen(Qt::black);
        painter.setBrush(Qt::white);
        painter.drawRect(0, 0, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);
        QPoint offsetPoint(((Config::GetInstance()->imageSize - scaledImage.width()) / 2), ((Config::GetInstance()->imageSize - scaledImage.height()) / 2));
        painter.drawImage(offsetPoint, scaledImage);
    }
}

void TaskTab::SaveNewTask()
{
    QFileDialog *saveDialog = new QFileDialog();
    saveDialog->setAcceptMode(QFileDialog::AcceptSave);
    saveDialog->setDefaultSuffix("bmp");

    if(saveDialog->exec())
        if((saveDialog->selectedFiles()).size() > 0)
            pattern->save((saveDialog->selectedFiles())[0]);
}
