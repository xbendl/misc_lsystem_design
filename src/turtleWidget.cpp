#include "turtleWidget.h"

using namespace std;

TurtleWidget::TurtleWidget(QWidget *parent) : QWidget(parent)
{
    // Globalni nastaveni
    setAutoFillBackground(true);
    setMouseTracking(true);
    setCursor(Qt::PointingHandCursor);

    showImage = true;

    update();
}

void TurtleWidget::paintEvent(QPaintEvent * /* event */)
{
    QPainter painter(this);

    // Vykresleni okraju
    painter.setPen(Qt::black);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, (this->width() - 1), (this->height() - 1));

    // Vykresleni obrazku
    if(this->showImage)
    {
        QPoint offsetPoint(((this->width() - image.width()) / 2), ((this->height() - image.height()) / 2));
        painter.drawImage(offsetPoint, image);
    }
}

void TurtleWidget::SetImage(QImage image)
{
    this->image = image;
    this->showImage = true;
    update();
}

void TurtleWidget::ClearWidget()
{
    this->showImage = false;
    update();
}
