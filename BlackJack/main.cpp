#include <iostream>
#include <string>
#include <memory>
#include "strategy.h"
#include "settings.h"
#include "game.h"

int main(int argc , char *argv[]){
    if (argc < 3){
        std::cout << "wrong number of arguments"<< std::endl;
        return 1;
    }
    Options options = Settings(argc,argv).getOptions();

    if(options.gameType == "wrong" || options.cardType < 0 || options.strategy.size() < 2){
        return 1;
    }

    std::unique_ptr<Game> game;
    if(options.gameType == "fast"){
        game = ((std::unique_ptr<Game>)new FastGame(options));
    }
    if(options.gameType == "detailed"){
        game = ((std::unique_ptr<Game>)new DetailedGame(options));
    }
    if( options.gameType == "tournament"){
        game = ((std::unique_ptr<Game>)new TournamentGame(options));
    }
    game->play();
    return 0;
}