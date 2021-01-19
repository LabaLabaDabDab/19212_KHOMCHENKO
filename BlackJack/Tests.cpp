#include "gtest/gtest.h"

#include "blackjack.h"
#include "factory.h"
#include "game.h"
#include "string"

namespace {
    class BlackJackTest : public ::testing::Test {};
    TEST_F(BlackJackTest, fast) {
        srand(time(0));
        GConfigs config;
        config.cMod = CardGivMode::SIMPLE;
        config.countStr = 2;
        config.deckSize = 3;
        config.gMod = GameMode::FAST;
        std::vector<std::unique_ptr<Strategy>> strategies(0);
        Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
        std::vector<std::string> ID = {"first", "second"};
        for (int i = 0; i < ID.size(); ++i) {
            Strategy * (*function)() = f->createStrategyByID(ID[i]);
            if (nullptr == function) {
                std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
                continue;
            }
            strategies.emplace_back(function());
        }

        Game game(config, std::move(strategies));
        game.Play();
        auto winner = game.getWinners();
        EXPECT_TRUE(winner.back() == 0 || winner.back() == 1 );
    }

    TEST_F(BlackJackTest, DETAILED) {
        srand(time(0));
        GConfigs config;
        config.cMod = CardGivMode::DEFAULT;
        config.countStr = 2;
        config.deckSize = 3;
        config.gMod = GameMode::DETAILED;
        std::vector<std::unique_ptr<Strategy>> strategies(0);
        Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
        std::vector<std::string> ID = {"first", "second"};
        for (int i = 0; i < ID.size(); ++i) {
            Strategy * (*function)() = f->createStrategyByID(ID[i]);
            if (nullptr == function) {
                std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
                continue;
            }
            strategies.emplace_back(function());
        }

        Game game(config, std::move(strategies));
        game.Play();
        auto winner = game.getWinners();
        EXPECT_TRUE(winner.back() == 0 || winner.back() == 1 );
    }

    TEST_F(BlackJackTest, TOURNAMENT_3_without_txt) {
        srand(time(0));
        GConfigs config;
        config.cMod = CardGivMode::DEFAULT;
        config.countStr = 3;
        config.deckSize = 1;
        config.gMod = GameMode::TOURNAMENT;
        std::vector<std::unique_ptr<Strategy>> strategies(0);
        Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
        std::vector<std::string> ID = {"first", "second", "dominate"};
        for (int i = 0; i < ID.size(); ++i) {
            Strategy * (*function)() = f->createStrategyByID(ID[i]);
            if (nullptr == function) {
                std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
                continue;
            }
            strategies.emplace_back(function());
        }

        Game game(config, std::move(strategies));
        game.Play();
        auto winner = game.getWinners();
        EXPECT_TRUE(winner.back() == 0 || winner.back() == 1 || winner.back() == 2);
    }

    TEST_F(BlackJackTest, TOURNAMENT_4_txt) {
        srand(time(0));
        GConfigs config;
        config.configDir = "C:\\Users\\1604701\\CLionProjects\\BlackJack2\\cmake-build-debug";
        config.cMod = CardGivMode::DEFAULT;
        config.countStr = 4;
        config.deckSize = 1;
        config.gMod = GameMode::TOURNAMENT;
        std::vector<std::unique_ptr<Strategy>> strategies(0);
        Factory<std::string, Strategy * (*)()> * f = Factory<std::string, Strategy * (*)()>::getInstance();
        std::vector<std::string> ID = {"first", "second", "multi", "other"};
        for (int i = 0; i < ID.size(); ++i) {
            Strategy * (*function)() = f->createStrategyByID(ID[i]);
            if (nullptr == function) {
                std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
                continue;
            }
            strategies.emplace_back(function());
        }

        Game game(config, std::move(strategies));
        game.Play();
        auto winner = game.getWinners();
        EXPECT_TRUE(winner.back() == 0 || winner.back() == 1 || winner.back() == 2 || winner.back() == 3);
    }

    TEST_F(BlackJackTest, TOURNAMENT_fake) {
        srand(time(0));
        try {
            GConfigs config;
            config.configDir = "C:\\Users\\1604701\\CLionProjects\\BlackJack2\\cmake-build-debug";
            config.cMod = CardGivMode::DEFAULT;
            config.countStr = 2;
            config.deckSize = 1;
            config.gMod = GameMode::TOURNAMENT;
            std::vector<std::unique_ptr<Strategy>> strategies(0);
            Factory<std::string, Strategy *(*)()> *f = Factory<std::string, Strategy *(*)()>::getInstance();
            std::vector<std::string> ID = {"first", "second", "multi"};
            for (int i = 0; i < ID.size(); ++i) {
                Strategy *(*function)() = f->createStrategyByID(ID[i]);
                if (nullptr == function) {
                    std::cerr << "Unikown strategy ID " << ID[i] << std::endl;
                    continue;
                }
                strategies.emplace_back(function());
            }
            Game game(config, std::move(strategies));
            game.startGame();
        } catch (std::exception &) {
            EXPECT_TRUE(true);
        }
    }
}