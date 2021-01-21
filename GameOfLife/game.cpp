#include <QFile>
#include <QString>
#include <QTextStream>

#include "game.h"

std::pair<size_t, size_t> Game::maxSize = std::make_pair(500,500);
std::pair<size_t, size_t> Game::minSize = std::make_pair(10,10);

Game::Game(std::pair<size_t, size_t> sz) :
    size(sz)
{
    rangeB = {false, false, false, true, false, false, false, false, false};
    rangeS = {false, false, true, true, false, false, false, false, false};
    universe.resize((size.first) * (size.second));
    generation.resize((size.first) * (size.second));
}

bool Game::newGenerate()
{
    size_t notChanged = 0;
    generation.clear();
    generation.resize((size.first) * (size.second));
    for(size_t x = 0; x < size.first; x++) {
        for(size_t y = 0; y < size.second; y++) {
            generation[y * size.first + x] = willAlive(x,y);
            if(generation[y * size.first + x] == universe[y * size.first + x])
                notChanged++;
        }
    }
    if(notChanged == size.first * size.second) {
        return false;
    }
    universe = generation;
    return true;
}

bool Game::isAlive(size_t x, size_t y)
{
    return universe[y * size.first +  x];
}

bool Game::willAlive(size_t x, size_t y)
{
    int power = 0;
    size_t prev_x = (x > 0 ? x - 1 : size.first - 1),
        prev_y = (y > 0 ? y - 1 : size.second - 1),
        next_x = (x < size.first - 1 ? x + 1 : 0),
        next_y = (y < size.second - 1 ? y + 1 : 0);
    power += universe[prev_y * size.first +  x];
    power += universe[next_y * size.first +  x];
    power += universe[y * size.first +  next_x];
    power += universe[y * size.first +  prev_x];
    power += universe[prev_y * size.first +  prev_x];
    power += universe[prev_y * size.first +  next_x];
    power += universe[next_y * size.first +  prev_x];
    power += universe[next_y * size.first +  next_x];
    if (!isAlive(x,y) && rangeB[power])
           return true;
    if (isAlive(x,y) && rangeS[power])
           return true;
    return false;
}

void Game::reset()
{
    universe.clear();
    generation.clear();
    universe.resize((size.first) * (size.second));
    generation.resize((size.first) * (size.second));
}

void Game::resize(std::pair<size_t, size_t> newSize)
{
    size = newSize;
    reset();
}

void Game::setHeight(size_t height)
{
    size.second = height;
}

void Game::setWidth(size_t width)
{
    size.first = width;
}

void Game::setCellAlive(size_t x, size_t y)
{
    universe[y * size.first +  x] = true;
}

void Game::setCellDead(size_t x, size_t y)
{
    universe[y * size.first + x] = false;
}

void Game::setCellReverse(size_t x, size_t y)
{
    universe[y * size.first + x] = !universe[y * size.first + x];
}

const std::vector<bool> & Game::getUniverse() const
{
    return universe;
}

const std::pair<size_t, size_t> & Game::getSize() const
{
    return size;
}

void Game::setMinSize(std::pair<size_t, size_t> newMin)
{
    Game::minSize = newMin;
}

void Game::setMaxSize(std::pair<size_t, size_t> newMax)
{
    Game::maxSize = newMax;
}

const std::pair<size_t, size_t> & Game::getMaxSize() const
{
    return Game::maxSize;
}

const std::pair<size_t, size_t> & Game::getMinSize() const
{
    return Game::minSize;
}

void Game::dump(QString & data)
{
    data.clear();
    char temp;
    for(size_t y = 0u; y < size.second; y++) {
        for(size_t x = 0u; x < size.first; x++) {
            if(isAlive(x,y) == true) {
                temp = '*';
            } else {
                temp = 'o';
            }
            data.append(temp);
        }
        data.append("\n");
    }
}

void Game::setDump(const QString & data)
{
    int current = 0;
    reset();
    for(size_t y = 0u; y < size.second; y++) {
        for(size_t x = 0u; x < size.first; x++) {
            if(data[current] == '*')
                universe[y * size.first + x] = true;
            current++;
        }
        current++;
    }
}

Game::configs Game::load(QTextStream & in)
{
    Game::configs par;
    par.ruleB = in.readLine();
    par.ruleS = in.readLine();

    in >> par.square;  
    in >> par.w;
    in >> par.h;

    if (par.square < 0 || par.square > 1 || par.w < 10 || par.w > 500 || par.h < 10 || par.h > 500)
        throw (std::exception());

    size.first = static_cast<size_t>(par.w);
    size.second = static_cast<size_t>(par.h);

    QString data;

    for(int k=0; k < par.h ; k++) {
        QString t;
        in >> t;
        data.append(t + "\n");
    }
    setDump(data);

    in >> par.r >> par.g >> par.b;
    if (par.r < 0 || par.r > 255 || par.g < 0 || par.g > 255 || par.b < 0 || par.b > 255)
        throw (std::exception());

    in >> par.t;
    if (par.t < 50 || par.t > 1000)
        throw (std::exception());

    return par;
}

void Game::save(QFile & file, const configs & conf)
{
    QString buf = conf.ruleB + "\n" + conf.ruleS + "\n";
    file.write(buf.toUtf8());
    buf.clear();

    buf = QString::number(conf.square) + "\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(static_cast<int>(size.first)) + "\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(static_cast<int>(size.second)) + "\n";
    file.write(buf.toUtf8());

    buf.clear();
    dump(buf);
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(conf.r) + " " +
          QString::number(conf.g) + " " +
          QString::number(conf.b) + "\n";
    file.write(buf.toUtf8());

    buf.clear();
    buf = QString::number(conf.t) + "\n";
    file.write(buf.toUtf8());
}

void Game::setRuleB(QString B){
    for (int i = 0; i < 9; i++){
        rangeB[i] = false;
    }
    for (char c: B.toStdString()){
        if (c >= '0' && c <= '9') {
            rangeB[static_cast<int>( c - '0')] = true;
        }
    }
}

void Game::setRuleS(QString S){
    for (int i = 0; i < 9; i++){
        rangeS[i] = false;
    }
    for (char c: S.toStdString()){
        if (c >= '0' && c <= '9') {
            rangeS[static_cast<int>( c - '0')] = true;
        }
    }
}

