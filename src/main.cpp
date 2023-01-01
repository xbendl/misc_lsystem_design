#include <QtGui>
#include <time.h>
#include "tabDialog.h"

int main(int argc, char *argv[])
{
    srand(time(NULL));

    // Start aplikace
    QApplication app(argc, argv);
    TabDialog tabDialog;
    tabDialog.show();

    return app.exec();
}
