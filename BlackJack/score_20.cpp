#ifndef SCORE_20_H_
#define SCORE_20_H_
#include "factory.h"
#include "strategy.h"

class Score_20: public Strategy{
public:
    Score_20(){
        name = "score_20";
    }

    void turn(int c , int dealerFirst) override {
        score += c;
        if(score >= 20){
            pass = true;
        }
    }
};

#endif