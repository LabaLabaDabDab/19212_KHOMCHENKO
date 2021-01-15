#ifndef DEALER_H_
#include "factory.h"
#include "strategy.h"

class Dealer: public Strategy{
public:
    Dealer(){
        name = "Dealer";
    }
    void turn(int c , int First) override {
        score += c;
        if(score >= 17){
            pass = true;
        }
    }
};



#endif