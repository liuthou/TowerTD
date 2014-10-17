#ifndef _AIPlAYER_H_
#define _AIPlAYER_H_

#include "Player.h"

using namespace TexasPoker;

class AIPlayer : public Player {
public:
	static AIPlayer* create(ePlayerGameState playerGameState, int id, std::string name, char sex, 
		int totalScore, int roomLimitedScore);
	bool init(ePlayerGameState playerGameState, int id, std::string name, char sex, 
		int totalScore, int roomLimitedScore);
};
#endif