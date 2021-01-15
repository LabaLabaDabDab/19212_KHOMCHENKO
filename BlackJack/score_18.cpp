#ifndef SCORE_18_H_
#define SCORE_18_H_
#include "factory.h"
#include "strategy.h"

class Score_18: public Strategy{
public:
    Score_18(){
        name = "score_18";
    }

    void turn(int c , int dealerFirst) override {
        score += c;
        if(score >= 18){
            pass = true;
        }
    }
};

namespace {
    bool b = Factory<Strategy, Strategy*(*)(), std::string>::
    get_instance()->register_strat("Score_18", Creator<Score_18, Strategy>::create);
}

#endif
