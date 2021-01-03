#include <QColorDialog>
#include <QFile>
#include <QFileDialog>
#include <QString>
#include <QTextStream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    currentColor(QColor("#000"))
{
    ui->setupUi(this);

    QPixmap icon(16, 16);
    icon.fill(ui->game->masterColor());
    ui->colorButton->setIcon( QIcon(icon) );

    ui->colorButton->setIcon(QIcon(icon));
    ui->widthSlider->setRange(ui->game->minWidth(), ui->game->maxWidth());
    ui->heightSlider->setRange(ui->game->minHeight(), ui->game->maxHeight());
    ui->intervalSlider->setRange(50, 1000);
    ui->widthSlider->setValue(ui->game->fieldWidth());
    ui->heightSlider->setValue(ui->game->fieldHeight());
    ui->intervalSlider->setValue(ui->game->interval());
    ui->squareButton->click();

    connect(ui->StartButton, SIGNAL(clicked()), ui->game, SLOT(startGame()));
    connect(ui->StopButton, SIGNAL(clicked()), ui->game,SLOT(stopGame()));
    connect(ui->ClearButton, SIGNAL(clicked()), ui->game,SLOT(clear()));
    connect(ui->applyButton, SIGNAL(clicked()), ui->game, SLOT(setParametrs()));

    connect(ui->widthSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setFieldWidth(int)));
    connect(ui->heightSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setFieldHeight(int)));
    connect(ui->intervalSlider, SIGNAL(valueChanged(int)), ui->game, SLOT(setInterval(int)));


    connect(ui->game, SIGNAL(gameStart(bool)), ui->applyButton, SLOT(setDisabled(bool)));
    connect(ui->game, SIGNAL(gameEnds(bool)), ui->applyButton, SLOT(setEnabled(bool)));

    connect(ui->customButton,SIGNAL(toggled(bool)), ui->game, SLOT(setCustomField(bool)));
    connect(ui->squareButton,SIGNAL(toggled(bool)), ui->game, SLOT(setSquareField(bool)));
    connect(ui->game, SIGNAL(heightChanged(int)), ui->heightSlider, SLOT(setValue(int)));
    connect(ui->game, SIGNAL(widthChanged(int)), ui->widthSlider, SLOT(setValue(int)));

    connect(ui->colorButton, SIGNAL(clicked()), this, SLOT(selectMasterColor()));

    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveGame()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadGame()));
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::selectMasterColor()
{
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    if(!color.isValid())
        return;
    currentColor = color;
    ui->game->setMasterColor(color);
    QPixmap icon(16, 16);
    icon.fill(color);
    ui->colorButton->setIcon( QIcon(icon) );
}

void MainWindow::saveGame()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                tr("Save current game"),
                            QDir::homePath(),
                                tr("Conway's Game *.life Files (*.life)"));
    if(filename.length() < 1)
        return;

    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;

    Game::configs conf;

    conf.square = ui->game->square();
    QColor color = ui->game->masterColor();
    conf.r = color.red();
    conf.g = color.green();
    conf.b = color.blue();
    conf.t = ui->intervalSlider->value();

    ui->game->game.save(file, conf);

    file.close();
}

void MainWindow::loadGame()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                tr("Open saved game "),
                        QDir::homePath(),
                                tr("Conway's Game of Life file (*.life)"));
    if(filename.length() < 1)
        return;
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly))
        return;
    QTextStream in(&file);

    Game::configs conf = ui->game->game.load(in);
    ui->game->update();



    ui->widthSlider->setValue(conf.w);
    ui->heightSlider->setValue(conf.h);

    if(conf.square == 1)
        ui->squareButton->click();
    else
        ui->customButton->click();

    currentColor = QColor(conf.r,conf.g,conf.b);
    ui->game->setMasterColor(currentColor);
    QPixmap icon(16, 16);
    icon.fill(currentColor);
    ui->colorButton->setIcon( QIcon(icon) );

    ui->intervalSlider->setValue(conf.t);
    ui->game->setInterval(conf.t);

    file.close();
}

