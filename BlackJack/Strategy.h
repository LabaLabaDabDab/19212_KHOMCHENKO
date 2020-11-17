#ifndef UNTITLED7_STRATEGY_H
#define UNTITLED7_STRATEGY_H

#pragma once
class Strategy
{
public:
    // Чисто виртуальный метод, который переопределяет поведение стратегии
    virtual void OnMadeStep() = 0;
};

#endif //UNTITLED7_STRATEGY_H
