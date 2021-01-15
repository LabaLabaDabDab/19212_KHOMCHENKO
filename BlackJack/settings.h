#ifndef SETTINGS_H_
#define SETTINGS_H_

#include <vector>

struct Options{
    std::string gameType;
    int cardType;
    std::vector<Strategy*> strategy;
};

class Settings{
public:
    Settings(int argc , char *argv[]){
        options.gameType = setGame(argv[1]);
        options.cardType = setCard(argv[2]);
        options.strategy = createStrategy(argc , argv);
    }

    Settings(const Settings& b ){
        options.gameType = b.options.gameType;
        options.cardType = b.options.cardType;
        options.strategy = b.options.strategy;
    }

    std::string setGame(std::string str){
        if(str == "fast")
            return "fast";
        if( str == "detailed")
            return "detailed";
        if( str == "tournament")
            return "tournament";
        std::cout << "wrong gameType" << std::endl;
        return "wrong";
    }

    int setCard(std::string str){
        if(str == "simple deck")
            return 0;
        if(str == "one deck")
            return 1;
        if(str == "N deck"){
            int N = 0;
            std::cout << "please enter decks number" << std::endl;
            std::cin  >> N;
            return N;
        }
        std::cout << "wrong cardType" << std::endl;
        return (-1);
    }

    std::vector<Strategy*> createStrategy(int argc , char *argv[]){
        std::vector<Strategy*> strategy;
        if(options.gameType == "tournament" && argc < 4){
            std::cout <<"not enought players to tournament"<< std::endl;
            return strategy;
        }
        if(options.gameType != "tournament"){
            strategy.push_back(Factory<Strategy, Strategy*(*)(), std::string>::get_instance()->create("Dealer"));
        }
        for(int i = 3 ; i < argc ; i++){
            if (Factory<Strategy, Strategy*(*)(), std::string>::get_instance()->isRegistered(argv[i]) == false)
                std::cout << "unknown player : " << argv[i] <<std::endl;
            else
                strategy.push_back(Factory<Strategy, Strategy*(*)(), std::string>::get_instance()->create(argv[i]));
        }
        return strategy;
    }

    Options getOptions(){
        return options;
    }

private:
    Options options;
};

#endif
