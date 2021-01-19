#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QMainWindow>

class GameWidget;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget * parent = nullptr);
    ~MainWindow();

public slots:
    void selectMasterColor();
    void loadGame();
    void saveGame();

private slots:
    void on_pushButton_clicked();

    void on_sButton_valueChanged(int arg1);

private:
    Ui::MainWindow * ui;
    QColor currentColor;
};

#endif // MAINWINDOW_H
