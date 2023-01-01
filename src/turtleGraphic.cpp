#include "turtleGraphic.h"

using namespace std;

void TurtleGraphic::ScaleImage(QImage &image, QImage &scaledImage, int maxWidth, int maxHeight)
{
    double multConstantX = (double) maxWidth / image.width();
    double multConstantY = (double) maxHeight / image.height();
    double multConstant  = (multConstantX < multConstantY) ? multConstantX : multConstantY;

    QSize newSize(multConstant * image.width(), multConstant * image.height());
    scaledImage = image.scaled(newSize);
}

void TurtleGraphic::CropImage(QImage &pattern, QImage &croppedPattern)
{
    // Zjisteni souradnic pro nasledne oriznuti (vymazani prazdnych radku a sloupcu z kraju obrazku)
    QPoint startPoint(0, 0);
    QPoint endPoint(pattern.width(), pattern.width());
    bool found = false;
    for(int i = 0; i < pattern.width(); i++)
    {
        for(int j = 0; j < pattern.height(); j++)
        {
            if(qRed(pattern.pixel(i, j)) == 0)
            {
                startPoint.setX(i);
                found = true;
                break;
            }
        }
        if(found)
            break;
    }
    found = false;
    for(int i = (pattern.width() - 1); i >= 0; i--)
    {
        for(int j = 0; j < pattern.height(); j++)
        {
            if(qRed(pattern.pixel(i, j)) == 0)
            {
                endPoint.setX(i);
                found = true;
                break;
            }
        }
        if(found)
            break;
    }
    found = false;
    for(int i = 0; i < pattern.height(); i++)
    {
        for(int j = 0; j < pattern.width(); j++)
        {
            if(qRed(pattern.pixel(j, i)) == 0)
            {
                startPoint.setY(i);
                found = true;
                break;
            }
        }
        if(found)
            break;
    }
    found = false;
    for(int i = (pattern.height() - 1); i >= 0; i--)
    {
        for(int j = 0; j < pattern.width(); j++)
        {
            if(qRed(pattern.pixel(j, i)) == 0)
            {
                endPoint.setY(i);
                found = true;
                break;
            }
        }
        if(found)
            break;
    }

    // Oriznuti obrazku
    QImage resultImage((endPoint.x() - startPoint.x() + 1), (endPoint.y() - startPoint.y() + 1), QImage::Format_Mono);
    resultImage = pattern.copy(startPoint.x(), startPoint.y(), (endPoint.x() - startPoint.x() + 1), (endPoint.y() - startPoint.y() + 1));
    croppedPattern = resultImage;
}

QImage TurtleGraphic::CreateImage(string generatedString, float angle)
{
    float step = 100;     // nahodne nastavena nejaka magicka hodnota (bude prepocitana podle potreby)
    double x, y;
    double minX, minY;
    double maxX, maxY;
    double actAngle = 0.5 * M_PI;
    x = y = 0;
    minX = minY = 0;
    maxX = maxY = INT_MIN;
    stack<tTurtleState> turtleState;
    tTurtleState dummyState;

    // Pruchod pres vygenerovany retezec pro zjisteni rozsahu hodnot
    for(int i = 0; i < (int)generatedString.size(); i++)
    {
        // Posun dle aktualniho znaku retezce
        switch(generatedString[i])
        {
            case 'F':
                x += step * cos(actAngle);
                y += step * sin(actAngle);
                break;
            case 'f':
                x += step * cos(actAngle);
                y += step * sin(actAngle);
                break;
            case '+':
                actAngle += angle;
                break;
            case '-':
                actAngle -= angle;
                break;
            case '|':
                actAngle += (actAngle + M_PI);
                break;
            case '[':
                dummyState.x = x;
                dummyState.y = y;
                dummyState.angle = actAngle;
                turtleState.push(dummyState);
                break;
            case ']':
                dummyState = turtleState.top();
                x = dummyState.x;
                y = dummyState.y;
                actAngle = dummyState.angle;
                turtleState.pop();
                break;
        }

        // Aktualizace krajnich souradnic
        if(x > maxX)
            maxX = x;
        if(x < minX)
            minX = x;
        if(y > maxY)
            maxY = y;
        if(y < minY)
            minY = y;
    }
    if(floor(minX + 0.5) == floor(maxX + 0.5))
        maxX = minX + 1;
    if(floor(minY + 0.5) == floor(maxY + 0.5))
        maxY = minY + 1;

    // Urceni delky kroku
    double dx = maxX - minX;
    double dy = maxY - minY;
    double multConstX = ((double)(Config::GetInstance()->imageSize - 1) / dx);
    double multConstY = ((double)(Config::GetInstance()->imageSize - 1) / dy);
    double multConst = (multConstX < multConstY) ? multConstX : multConstY;
    step = multConst * step;

    // Urceni startovaciho bodu
    if(multConstX > multConstY)
    {
        //x = abs(minX) / (abs(minX) + maxX) * (Config::GetInstance()->imageSize - 1) + ((1 - (1 / (multConstX / multConstY))) * (maxX-minX) / 2);
        x = abs(minX) / (abs(minX) + maxX) * (Config::GetInstance()->imageSize - 1);
        y = abs(minY) / (abs(minY) + maxY) * (Config::GetInstance()->imageSize - 1);

        /*int offsetX = (Config::GetInstance()->imageSize - multConstY * dx) / 2;
        if((x + offsetX) < Config::GetInstance()->imageSize)
            x += offsetX;
        else
            x -= offsetX;*/
    }
    else
    {
        x = abs(minX) / (abs(minX) + maxX) * (Config::GetInstance()->imageSize - 1);
        y = abs(minY) / (abs(minY) + maxY) * (Config::GetInstance()->imageSize - 1);

        int offsetY = (Config::GetInstance()->imageSize - multConstX * dy) / 2;
        if((y + offsetY) < Config::GetInstance()->imageSize)
            y += offsetY;
        else
            y -= offsetY;
    }
    actAngle = 0.5 * M_PI;

    // Druhy pruchod s vyuzitim znalosti prepocitane delky kroku
    QPainterPath path;
    path.moveTo(x, Config::GetInstance()->imageSize - y);
    for(int i = 0; i < (int)generatedString.size(); i++)
    {
        // Posun dle aktualniho znaku retezce
        switch(generatedString[i])
        {
            case 'F':
                x += step * cos(actAngle);
                y += step * sin(actAngle);
                path.lineTo(floor(x + 0.49), (Config::GetInstance()->imageSize - 1) - floor(y + 0.49));
                break;
            case 'f':
                x += step * cos(actAngle);
                y += step * sin(actAngle);
                path.moveTo(floor(x + 0.49), (Config::GetInstance()->imageSize - 1) - floor(y + 0.49));
                break;
            case '+':
                actAngle += angle;
                break;
            case '-':
                actAngle -= angle;
                break;
            case '|':
                actAngle += (actAngle + M_PI);
                break;
            case '[':
                dummyState.x = x;
                dummyState.y = y;
                dummyState.angle = actAngle;
                turtleState.push(dummyState);
                break;
            case ']':
                dummyState = turtleState.top();
                x = dummyState.x;
                y = dummyState.y;
                actAngle = dummyState.angle;
                turtleState.pop();
                path.moveTo(floor(x + 0.49), (Config::GetInstance()->imageSize - 1) - floor(y + 0.49));
                break;
        }
    }

    // Vykresleni tvaru dle ulozene cesty
    QImage *pattern = new QImage(Config::GetInstance()->imageSize, Config::GetInstance()->imageSize, QImage::Format_Mono);

    QPainter painter(pattern);
    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.drawRect(0, 0, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);
    painter.setPen(Qt::black);
    painter.drawPath(path);

    QImage viewImage(Config::GetInstance()->imageSize, Config::GetInstance()->imageSize, QImage::Format_Mono);
    viewImage = pattern->copy(0, 0, Config::GetInstance()->imageSize, Config::GetInstance()->imageSize);

    return viewImage;
}
