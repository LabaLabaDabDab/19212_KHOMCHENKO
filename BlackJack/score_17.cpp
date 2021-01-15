#ifndef SCORE_17_H_
#define SCORE_17_H_
#include "factory.h"
#include "strategy.h"

class Score_17: public Strategy{
public:
    Score_17(){
        name = "Score_17";
    }
    void turn(int c , int dealerFirst) override {
        score += c;
        if(score >= 17){
            pass = true;
        }
    }
};

#endif
