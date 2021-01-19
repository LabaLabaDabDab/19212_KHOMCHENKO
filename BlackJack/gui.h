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
};
#endif