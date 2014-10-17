#include "NormalPlayer.h"

using namespace TexasPoker;

NormalPlayer* NormalPlayer::create(ePlayerGameState playerGameState, int id, std::string name, char sex, 
								   int totalScore, int roomLimitedScore){
	NormalPlayer* Nplayer = new NormalPlayer();


	if (Nplayer && Nplayer->init(playerGameState, id, name, sex, totalScore, roomLimitedScore))
	{
		Nplayer->autorelease();
        Nplayer->playerType = ePlayerType::NORMAL;

		return Nplayer;
	}
	CC_SAFE_DELETE(Nplayer);
	return nullptr;
}

bool NormalPlayer::init(ePlayerGameState playerGameState, int id, std::string name, char sex, 
						int totalScore, int roomLimitedScore){
	if (!Player::init(playerGameState, id, name, sex, totalScore, roomLimitedScore))
	{
		return false;
	}

	return true;
}

