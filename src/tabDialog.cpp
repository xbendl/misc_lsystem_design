#include "tabDialog.h"

TabDialog::TabDialog(QWidget *parent) : QDialog(parent)
{
    qRegisterMetaType<tIndividual>("tIndividual");

    // Globalni nastaveni aplikace
    setFixedSize(914, 470);
    setFont(QFont("Helvetica", 9, QFont::Normal));
    setWindowTitle(tr("L-Systemy & Evolucni algoritmy"));

    // Pridani zalozek
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new EvolutionManagerTab(this), tr("Manazer evoluce"));
    tabWidget->addTab(new TaskTab(this), tr("Spravce uloh"));
    tabWidget->setFixedSize(914, 470);
}

