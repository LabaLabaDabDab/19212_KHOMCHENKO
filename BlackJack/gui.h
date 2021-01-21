#ifndef GUI_H
#define GUI_H

#include <vector>

class Game;

class Gui {
	Game * game;
	Gui() = delete;
public:
	Gui(Game * const other) : game(other) {}
	~Gui() {}
	void TurnResults(unsigned int i) const;
	void Results() const;
	void StrategiesList() const;
	void TableResults(const std::vector<unsigned char> & table) const;
	void TourneyResults(const std::vector<unsigned char> & results) const;
	void PressTurn() const;
	void LostTurn() const;
	void CoutWinners(unsigned int championNumber) const;
	void DrawTurn() const;
    void Start() const;
    void CountStr() const;
};
#endif