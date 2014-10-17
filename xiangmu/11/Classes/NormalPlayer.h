#ifndef _NORMALPLAYER_H_
#define _NORMALPLAYER_H_

#include "Player.h"
using namespace TexasPoker;

class NormalPlayer : public Player{
public:
	static NormalPlayer* create(ePlayerGameState playerGameState, int id, std::string name, char sex, 
		int totalScore, int roomLimitedScore);
	bool init(ePlayerGameState playerGameState, int id, std::string name, char sex, 
		int totalScore, int roomLimitedScore);
private:

};

#endif