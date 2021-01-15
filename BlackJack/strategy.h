#ifndef STRATEGY_H_
#define STRATEGY_H_

#include "factory.h"

class Strategy{
public:
    virtual void turn(int n , int dealerFirst){}

    void pickFirst(int n , int k , int dealerFirst){
        firstCard = n;
        score = n;
        turn(k , dealerFirst);
    }

    void setWin(){
        win = true;
    }

    bool isPass(){
        return pass;
    }

    bool isWinner(){
        return win;
    }

    int getScore(){
        return score;
    }

    int getFirst(){
        return firstCard;
    }

    std::string getName(){
        return name;
    }

    void reset(){
        firstCard = 0;
        score = 0;
        pass = false;
        win = false;
    }

    void operator =(const Strategy* b){
        name = b->name;
        firstCard = b->firstCard;
        score = b->score;
        pass = b->pass;
        win = b->win;
    }

protected:
    std::string name = "null";
    int firstCard = 0;
    int score = 0;
    bool pass = false;
    bool win = false;
};


#endif
