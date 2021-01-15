#ifndef SOFTHAND_H_
#define SOFTHAND_H_
#include "factory.h"
#include "strategy.h"

class Softhand: public Strategy{
public:
    Softhand(){
        name = "Softhand";
    }

    void turn(int c , int dealerFirst) override {
        score += c;
        if( (score == 18 && dealerFirst < 9) || score > 18){
            pass = true;
        }
    }
};

namespace {
    bool b = Factory<Strategy, Strategy*(*)(), std::string>::
    get_instance()->register_strat("Softhand", Creator<Softhand, Strategy>::create);
}

#endif