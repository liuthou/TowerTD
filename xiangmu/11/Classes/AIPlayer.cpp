#include "AIPlayer.h"

using namespace TexasPoker;

AIPlayer* AIPlayer::create(ePlayerGameState playerGameState, int id, std::string name, char sex, 
						   int totalScore, int roomLimitedScore){
	AIPlayer* AIplayer = new AIPlayer();


	if (AIplayer && AIplayer->init(playerGameState, id, name, sex, totalScore, roomLimitedScore))
	{
        AIplayer->playerType = ePlayerType::AI;
		AIplayer->autorelease();

		return AIplayer;
	}
	CC_SAFE_DELETE(AIplayer);
	return nullptr;
}

bool AIPlayer::init(ePlayerGameState playerGameState, int id, std::string name, char sex, 
					int totalScore, int roomLimitedScore){
	if (!Player::init(playerGameState, id, name, sex, totalScore, roomLimitedScore))
	{
		return false;
	}

	return true;
}