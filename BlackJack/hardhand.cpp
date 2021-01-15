#ifndef HARDHAND_H_
#define HARDHAND_H_
#include "factory.h"
#include "strategy.h"

class Hardhand: public Strategy{
public:
    Hardhand(){
        name = "Hardhand";
    }
    void turn(int c , int dealerFirst) override {
        score += c;
        if( score == 12 && dealerFirst < 7 && dealerFirst > 3){
            pass = true;
        }
        if( score > 12 && score < 17 && dealerFirst < 7){
            pass = true;
        }
        if( score > 16){
            pass = true;
        }
    }
};

namespace {
    bool b = Factory<Strategy, Strategy*(*)(), std::string>::
    get_instance()->register_strat("Hardhand", Creator<Hardhand, Strategy>::create);
}

#endif