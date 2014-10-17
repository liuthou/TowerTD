//
//  Functon.h
//  TexasPoker的所有
//
//  标准化枚举, 标准化类
//
//  Created by 袁文龙 on 14-9-13.
//
//	 继尚 2014年 9.19 更改: 将class PokerArray; 等放入 namespace TexasPoker中
//                                        将文件名修正
//
//
//

#ifndef __TexasPoker__Functon__
#define __TexasPoker__Functon__

#include <iostream>
#include <cocos2d.h>
using namespace cocos2d;

namespace TexasPoker {


	class PokerArray;
	class Room;
	class Poker;
	class Hall;
	class Player;
	enum class PokerMethod;
	enum class pokerColor;


    /**公共函数库*/
    class Function{
		public:
        /**
         *  根据下注金额给予友好化金额
         *
         *  @param score 筹码数量
         *
         *  @return 返回一个友好的字符串例如; 12000 返回 1.2万  100.23万
         */
        static std::string getFormatScore(int score);
        
        /**
         *  根据牌型的枚举返回汉字
         *
         *  @param method 一个pokerMethod的枚举
         *
         *  @return 格式化后的汉字
         */
        static std::string getStringForPokerMethod(PokerMethod method);
        
        /**
         *  随机洗牌
         *
         *  @param pokers 传入一个已经生成完毕的PokerVector
         */
        static void randomVector(Vector<Poker *> & pokers);
        
        /**
         *  根据poker的数字和花色返回一个fileName
         *
         *  @return std::string fileName
         */
        static std::string getPokerFileNameByPokerNumberAndColor(int number,int color);
        
        /**
         *  通过两个Vec2 相对v1,v2的角度
         *
         *  @param v1 v1 description
         *  @param v2 v2 description
         *
         *  @return 角度
         */
        static float getAngleByVec21ANDVec22(Vec2 v1,Vec2 v2);
        
        /**根据玩家手牌和河牌获取比牌类型,判断的标准以大到小的方式来判断;
        @return PokerMethod 返回结果的玩法牌型
        */
        static PokerMethod getPokerMethodForHanderAndRiver(Player * player);

        /**根据扑克牌数组,从小到大,开始排序
        第一级排序: 2 -10 - J - A
        第二季排序: 红桃 - 梅花
        52张牌统一编号,用连号排序yguy
        */
        static Vector<Poker *> sortPokerArray(Vector<Poker *> &_pokerArray);

        /**根据扑克牌数组,获得是否皇家同花顺*/
        static bool isRoyalFlush(Vector<Poker *> _pokerArray);
        static bool isRoyalFlush(Player* player);

        /**根据扑克牌数组,同花顺,同花 + 顺子*/
        static bool isStraightFlush(Vector<Poker *> _pokerArray);
        static bool isStraightFlush(Player* player);
        /**根据扑克牌数组,四条, 4个数字一样 */
        static bool isFourOfAKind(Vector<Poker *> _pokerArray);
        static bool isFourOfAKind(Player* player);
        /**根据扑克牌数组,葫芦, 三条 + 一对*/
        static bool isFullhouse(Vector<Poker *> _pokerArray);
        static bool isFullhouse(Player* player);

        /**根据扑克牌数组,同花, 5张牌同色*/
        static bool isFlush(Vector<Poker *> _pokerArray);
        static bool isFlush(Player* player);

        /**根据扑克牌数组,顺子, 5张连号牌*/
        static bool isStraight(Vector<Poker *> _pokerArray);
        static bool isStraight(Player* player);
        /**根据扑克牌数组,三条, 3个牌数字一样*/
        static bool isThreeOfAKind(Vector<Poker *> _pokerArray);
        static bool isThreeOfAKind(Player* player);
        /**根据扑克牌数组,两对*/
        static bool isTwoPairs(Vector<Poker *> _pokerArray);
        static bool isTwoPairs(Player* player);

        /**根据扑克牌数组,一对*/
        static bool isOnePair(Vector<Poker *> _pokerArray);
        static bool isOnePair(Player* player);

        /**根据扑克牌数组,高牌*/
        static bool isHighCard(Vector<Poker *> _pokerArray);
        static bool isHighCard(Player* player);

        /**获取扑克牌花色, 参数只能是 int型的 1黑，2红， 3梅， 4方 */
        static pokerColor getPokerColor(int color);
        //pokerColor getRandomPokeColor();

        /**对每一轮的玩家，比较牌型，并将玩家按牌型从大到小放入数组，返回牌型最大的玩家*/
        Player * sortPlayerByCardType(Map<int, Player *> ChairsAtProcess);

        /**游戏清算; 根据牌桌上的所有玩家的手牌和河牌, 进行对比,最后计算奖金和胜负*/
        static void GameClearing(Room *room);

        /**论输赢---返回赢家*/
        static Vector<Player *> getWinners(Vector<Player *> vPlayer);
        
		/**赢家分钱*/
		static void winnersGetScore(int totalScore, Vector<Player *> winners);
    };
    
    class TP {
    public:
        static void log(const char * format, ...);
    };
    
}
#endif /* defined(__TexasPoker__Functon__) */
