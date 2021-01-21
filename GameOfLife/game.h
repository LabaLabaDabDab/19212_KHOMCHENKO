#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <QString>

class QTextStream;
class QFile;

class Game
{
public:
    struct configs {
        int w, h;
        int r, g, b;
        int t;
        int square;
        QString ruleB, ruleS;
    };
public:
    Game(std::pair<size_t, size_t> sz = minSize);
    ~Game() {}

    bool newGenerate();
    bool willAlive(size_t x, size_t y);
    bool isAlive(size_t x, size_t y);

    void reset();
    void resize(std::pair<size_t, size_t> newSize);
    void setHeight(size_t height);
    void setWidth(size_t width);
    void setRange(std::pair<int, int> newRange);
    void setCellAlive(size_t x, size_t y);
    void setCellDead(size_t x, size_t y);
    void setCellReverse(size_t x, size_t y);

    void dump(QString & data);
    void setDump(const QString & data);
    configs load(QTextStream & in);
    void save(QFile & file, const configs & conf);

    const std::vector<bool> & getUniverse() const;
    const std::pair<int, int> & getRange() const;
    const std::pair<size_t, size_t> & getSize() const;
    const std::pair<size_t, size_t> & getMaxSize() const;
    const std::pair<size_t, size_t> & getMinSize() const;

    static void setMinSize(std::pair<size_t, size_t> newMin);
    static void setMaxSize(std::pair<size_t, size_t> newMax);

    void setRuleB(QString B);
    void setRuleS(QString S);
private:

    static std::pair<size_t, size_t> maxSize;
    static std::pair<size_t, size_t> minSize;

    std::pair<size_t, size_t> size;
    std::vector<bool> rangeB;
    std::vector<bool> rangeS;
    std::vector<bool> universe;
    std::vector<bool> generation;

};

#endif // GAME_H
