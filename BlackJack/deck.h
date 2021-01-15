#ifndef DECK_H_
#define DECK_H_

class Deck{
public:
    virtual int pick(){}
};

class RandDeck: public Deck{
public:
    int pick() override{
        return (1 + (rand() % 10));
    }
};

class OneDeck: public Deck{
public:
    OneDeck(){
        for(int i = 0 ; i < 4 ; i++){
            for(int k = 1 ; k < 10 ; k++){
                cards.push_back(k);
            }
            for(int k = 0 ; k < 4 ; k++){
                cards.push_back(10);
            }
        }
    }

    int pick() override{
        int index = rand() % remainingCards;
        int num = cards[index];
        cards.erase(cards.begin() + index);
        remainingCards--;
        return num;
    }

private:
    int remainingCards = 52;
    std::vector<int> cards;
};

class CustomDeck: public Deck{
public:
    CustomDeck(int N){
        size *= N;
        remainingCards *= N;
        for(int j = 0 ; j < N ; j++){
            for(int i = 0 ; i < 4 ; i++){
                for(int k = 1 ; k < 10 ; k++){
                    cards.push_back(k);
                }
                for(int k = 0 ; k < 4 ; k++){
                    cards.push_back(10);
                }
            }
        }
    }

    int pick() override{
        int index = rand() % remainingCards;
        int num = cards[index];
        cards.erase(cards.begin() + index);
        remainingCards--;
        return num;
    }

private:
    int size = 52;
    int remainingCards = 52;
    std::vector<int> cards;
};

#endif
