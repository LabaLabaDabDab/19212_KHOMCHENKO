#ifndef GAME_H_
#define GAME_H_

#include "deck.h"
#include "settings.h"

class Game{
public:
    virtual void makeDeck(Options options){
        switch (options.cardType){
            case 0:{
                deck = (std::unique_ptr<Deck>)new RandDeck;
                break;
            }
            case 1:{
                deck = (std::unique_ptr<Deck>)new OneDeck;
                break;
            }
            default:{
                deck = (std::unique_ptr<Deck>)new CustomDeck(options.cardType);
            }
        }
    }

    virtual ~Game(){
        for(auto it : players){
            delete it;
        }
    }

    virtual void play(){}

    void checkResults(){
        int max;
        std::vector<int> index;
        for(int i = 0 ; i < players.size() ; i++){
            if((players[i]->getScore()) < 22){
                if((players[i]->getScore()) > max){
                    index.clear();
                    max = (players[i]->getScore());
                    index.push_back(i);
                }
                if((players[i]->getScore()) == max){
                    index.push_back(i);
                }
            }
        }
        for(int i = 0 ; i < index.size() ; i++){
            players[index[i]]->setWin();
        }
    }

    void showResult(){
        std::cout<<std::endl;
        std::cout<<"game over" <<std::endl;
        std::cout<<std::endl;
        for( auto i : players ){
            std::cout << i->getName() << std::endl;
            std::cout << "		score: " << i->getScore() << " ";
            if(i->isWinner())
                std::cout << "winner";
            std::cout << std::endl;
        }
    }

protected:
    std::unique_ptr<Deck> deck;
    std::vector<Strategy*> players;

};

class FastGame: public Game{
public:

    FastGame(Options options){
        makeDeck(options);
        players = options.strategy;
    }

    void play() override{
        for(auto it : players){
            if( it == players[0])
                it->pickFirst(deck->pick() , deck->pick() , players[0]->getFirst());
            else
                it->pickFirst(deck->pick() , deck->pick() , 0);
        }
        int passes = 0;
        while(passes != players.size()){
            passes = 0;
            for(auto it : players){
                if(!(it->isPass())){
                    it->turn(deck->pick() , players[0]->getFirst());
                }
                if(it->isPass()){
                    passes++;
                }
            }
        }
        checkResults();
        showResult();
    }

};

class DetailedGame: public Game{
public:
    DetailedGame(Options options){
        makeDeck(options);
        players = options.strategy;
    }

    void play() override{
        for(auto it : players){
            if( it == players[0])
                it->pickFirst(deck->pick() , deck->pick() , players[0]->getFirst());
            else
                it->pickFirst(deck->pick() , deck->pick() , 0);
            std::cout<< it->getName() << " : " << std::endl;
            std::cout<< "		score:" << it->getScore() <<std::endl;
            std::cout<< "		first card:" << it->getFirst() <<std::endl;
            std::cout<< "		pass:";
            if(it->isPass())
                std::cout<< "yes" <<std::endl;
            else
                std::cout<< "no" <<std::endl;
        }
        std::cout<<"============================="<<std::endl;
        int passes = 0;
        int turn = 1;
        while(passes != players.size()){
            std::cout<< "turn " << turn <<std::endl;
            passes = 0;
            for(auto it : players){
                if(!(it->isPass())){
                    it->turn(deck->pick() , players[0]->getFirst());
                }
                if(it->isPass()){
                    passes++;
                }
                std::cout<< it->getName() << " : " << std::endl;
                std::cout<< "		score:" << it->getScore() <<std::endl;
                std::cout<< "		pass:";
                if(it->isPass())
                    std::cout<< "yes" <<std::endl;
                else
                    std::cout<< "no" <<std::endl;
            }
            turn++;
            std::cout<<"============================="<<std::endl;
        }
        checkResults();
        showResult();
    }
};

class TournamentGame: public Game{
public:
    TournamentGame(Options options){
        makeDeck(options);
        players = options.strategy;
        wins = new int [players.size()];
        std::fill_n(wins , players.size() , 0);
    }

    ~TournamentGame(){
        for(auto it : players){
            delete it;
        }
        delete wins;
    }

    void play() override{
        for(int i = 0 ; i < (players.size() - 1) ; i++){
            for(int k = (i + 1) ; k < players.size() ; k++){
                int p1 = deck->pick();
                int p2 = deck->pick();
                players[i]->pickFirst( p1 , deck->pick() , p2);
                players[k]->pickFirst( p2 , deck->pick() , p1);
                int passes = 0;
                while(passes != 2){
                    passes = 0;
                    if(!(players[i]->isPass()))
                        players[i]->turn(deck->pick() , players[k]->getFirst());
                    if(players[i]->isPass()){
                        passes++;
                    }
                    if(!(players[k]->isPass()))
                        players[k]->turn(deck->pick() , players[i]->getFirst());
                    if(players[k]->isPass()){
                        passes++;
                    }
                }
                checkResults(i , k);
                players[i]->reset();
                players[k]->reset();
            }
        }
        checkTournament();
        showResult();
    }

    void checkResults(int i ,int k){
        if( (players[k]->getScore() < 22 ) || (players[i]->getScore() < 22 ) ){
            if( players[k]->getScore() == players[i]->getScore()){
                wins[i]++;
                wins[k]++;
            }
            if( players[k]->getScore() < players[i]->getScore() )
                wins[i]++;
            if( players[i]->getScore() < players[k]->getScore() )
                wins[k]++;
        }
    }

    void checkTournament(){
        int max = 0;
        std::vector<int> index;
        for(int i = 0 ; i < players.size() ; i++){
            if(wins[i] == max){
                index.push_back(i);
            }
            if(wins[i] > max){
                index.clear();
                max = wins[i];
                index.push_back(i);
            }
        }
        for(auto i : index){
            if( wins[i] > 0)
                players[i]->setWin();
        }
    }

    void showResult() {
        std::cout << std::endl;
        std::cout << "Tournament over" << std::endl;
        for(int i = 0 ; i < players.size() ; i++){
            std::cout << players[i]->getName() << " :" << std::endl;
            std::cout << "		wins: " << wins[i] << "  ";
            if(players[i]->isWinner())
                std::cout << "champion!"<< std::endl;
            else
                std::cout << std::endl;
            std::cout << std::endl;
        }
    }

private:
    int* wins;
};

#endif
