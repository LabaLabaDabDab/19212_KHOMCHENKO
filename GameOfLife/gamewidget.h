#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QWidget>

class QString;
class QTimer;

#include "game.h"

class GameWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);
    ~GameWidget() {}

    int maxWidth();
    int maxHeight();
    int minWidth();
    int minHeight();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent * e);
    void mouseMoveEvent(QMouseEvent * e);

signals:
    void environmentChanged(bool ok);
    void gameEnds(bool ok);
    void gameStart(bool ok);
    void heightChanged(int x);
    void widthChanged(int y);
    void bChanged(int b);
    void sChanged(int s);

public slots:
    void startGame();
    void stopGame();
    void clear();

    int fieldHeight();
    int fieldWidth();
    void setFieldHeight(int height);
    void setFieldWidth(int width);
    void setParametrs();

    void setSquareField(bool ok);
    void setCustomField(bool ok);
    int square();

    int interval();
    void setInterval(int msec);

    QColor masterColor();
    void setMasterColor(const QColor &color);

protected slots:
    void paintGrid(QPainter & p);
    void paintUniverse(QPainter & p);
    void newGeneration();

public:
    Game game;

private:
    QTimer * timer;
    QColor myMasterColor;
    QColor currentColor;

    size_t _width;
    size_t _height;
    bool _changed;
    bool _square;
};

#endif // GAMEWIDGET_H
