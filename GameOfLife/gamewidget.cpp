#include <QColorDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QPainter>
#include <QString>
#include <QTimer>

#include "gamewidget.h"

int GameWidget::interval()
{
    return timer->interval();
}

void GameWidget::setInterval(int msec)
{
    timer->setInterval(msec);
}

GameWidget::GameWidget(QWidget * parent) :
    QWidget(parent),
    timer(new QTimer(this)),
    myMasterColor("#ff5600"),
    _width(game.getMinSize().first),
    _height(game.getMinSize().second),
    _changed(false),
    _square(true)
{
    timer->setInterval(50);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

void GameWidget::newGeneration()
{
    if (game.newGenerate() == false) {
        QMessageBox::information(this,
                                 tr("Game lost sense"),
                                 tr("The End. Now game finished because all the next generations will be the same."),
                                 QMessageBox::Ok);
        stopGame();
        emit gameEnds(true);
    }

    update();
}

int GameWidget::fieldHeight()
{
    return static_cast<int>(game.getSize().first);
}

int GameWidget::fieldWidth()
{
    return static_cast<int>(game.getSize().second);
}

void GameWidget::setFieldHeight(int height)
{
    _changed = true;
    _height = static_cast<size_t>(height);
    emit heightChanged(height);
}

void GameWidget::setFieldWidth(int width)
{
    _changed = true;
    _width = static_cast<size_t>(width);
    if (_square) {
        _height = static_cast<size_t>(width);
        emit heightChanged(width);
    }
    emit widthChanged(width);
}

void GameWidget::setParametrs()
{
   if(_changed) {
        game.setWidth(_width);
        game.setHeight(_height);
        _changed = false;
        game.reset();
        update();
    }
}

void GameWidget::setSquareField(bool ){
    _square = true;
}

void GameWidget::setCustomField(bool )
{
    _square = false;
}

void GameWidget::startGame()
{
    timer->start();
    gameStart(true);
}

void GameWidget::stopGame()
{
    timer->stop();
    emit gameEnds(true);
}

void GameWidget::clear()
{
    game.reset();
    emit gameEnds(true);
    update();
}

QColor GameWidget::masterColor()
{
    return myMasterColor;
}

void GameWidget::setMasterColor(const QColor &color)
{
    myMasterColor = color;
    update();
}

void GameWidget::paintGrid(QPainter & p)
{
    QColor gridColor = ("#000");
    gridColor.setAlpha(150);
    QRect borders(0, 0, width() - 1, height() - 1);
    gridColor.setAlpha(10);
    p.setPen(gridColor);

    int cellWidth = static_cast<double>(width()) / game.getSize().first + 0.5;
    for(int k = cellWidth; k < width(); k += cellWidth)
        p.drawLine(k, 0, k, height());

    int cellHeight = static_cast<double>(height()) / game.getSize().second + 0.5;
    for(int k = cellHeight; k < height(); k += cellHeight)
        p.drawLine(0, k, width(), k);

    p.drawRect(borders);
}

void GameWidget::paintUniverse(QPainter & p)
{
    size_t x = 0u, y = 0u;
    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;

    for(y = 0u; y < game.getSize().second; y++) {
        for(x = 0u; x < game.getSize().first; x++) {
            if(game.isAlive(x,y) == true) {
                qreal left = static_cast<qreal>(cellWidth * x);
                qreal top  = static_cast<qreal>(cellHeight * y);

                QRectF r(left, top, static_cast<qreal>(cellWidth),
                                    static_cast<qreal>(cellHeight));

                p.fillRect(r, QBrush(myMasterColor));
            }
        }
    }
}

void GameWidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    paintGrid(p);
    paintUniverse(p);
}

void GameWidget::mousePressEvent(QMouseEvent *e)
{
    emit environmentChanged(true);
    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;
    size_t y = static_cast<size_t>(e->y() / cellHeight);
    size_t x = static_cast<size_t>(e->x() / cellWidth);

    game.setCellReverse(x, y);
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent * e)
{
    if (e->y() >= height() || e->y() < 0)
        return;
    if (e->x() >= width() || e->x() < 0)
        return;

    double cellWidth = static_cast<double>(width()) / game.getSize().first;
    double cellHeight = static_cast<double>(height()) / game.getSize().second;
    size_t y = static_cast<size_t>(e->y() / cellHeight);
    size_t x = static_cast<size_t>(e->x() / cellWidth);
    if(!game.isAlive(x, y)){
        game.setCellAlive(x, y);
        update();
    }
}

int GameWidget::maxHeight()
{
    return static_cast<int>(game.getMaxSize().second);
}

int GameWidget::minHeight()
{
    return static_cast<int>(game.getMinSize().second);
}

int GameWidget::maxWidth()
{
    return static_cast<int>(game.getMaxSize().first);
}

int GameWidget::minWidth()
{
    return static_cast<int>(game.getMinSize().first);
}

int GameWidget::square()
{
    return (_square ? 1 : 2);
}
