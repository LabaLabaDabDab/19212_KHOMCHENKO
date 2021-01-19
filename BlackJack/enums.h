#ifndef ENUMS_H
#define ENUMS_H

enum class Suits {
	HEART,
	DIAMOND,
	CLUB,
	SPARE
};

enum class Decision : bool {
	STOP = 0x1,
	NEXT = 0x0
};

enum class _Game : bool {
	YES = 0x1,
	NO = 0x0
};

enum class CardGivMode : unsigned char {
	SIMPLE = 0xFF,
	DEFAULT = 0x00
};

enum class GameMode : unsigned char {
	DETAILED = 0x00,
	FAST = 0x01,
	TOURNAMENT = 0x02
};
#endif // ENUMS_H