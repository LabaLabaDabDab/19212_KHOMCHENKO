#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QColor>
#include <QMainWindow>

#include <QTextStream>

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

private:
    Ui::MainWindow * ui;
    QColor currentColor;
    std::vector<std::string> splitString(const std::string &str, char ch);
    bool checkFile(const QTextStream &stream);
};

#endif // MAINWINDOW_H
