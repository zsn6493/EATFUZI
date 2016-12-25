#include "cocos2d.h"
USING_NS_CC;

class zombieInterface : public Node
{
public:
	virtual ~zombieInterface() = 0 {};

	virtual std::string getBattleName() = 0;
	virtual int getPepLevel() = 0;
	virtual int getiBaseAtk() = 0;
	virtual int getiCurAtk() = 0;
	virtual int getiHP() = 0;
	virtual int getiDefens() = 0;
	virtual int getiSpeed() = 0;
	virtual int getiAtkSpeed() = 0;
	virtual int getmoveType() = 0;
	virtual int getimoveStatus() = 0;
	virtual int getstartMoveAction() = 0;
	virtual int getstartFightAciton() = 0;

	virtual void setBattleName(std::string name) = 0;
	virtual void setPepLevel(int PepLevl) = 0;
	virtual void setiBaseAtk(int baseAtk) = 0;
	virtual void setiCurAtk(int iCurAtk) = 0;
	virtual void setiHP(int hp) = 0;
	virtual void setiDefens(int defens) = 0;
	virtual void setiSpeed(int speed) = 0;
	virtual void setiAtkSpeed(int atkSpeed) = 0;
	virtual void setmoveType(int moveType) = 0;
	virtual void setimoveStatus(int moveStatus) = 0;
	virtual void setstartMoveAction(int moveAction) = 0;
	virtual void setstartFightAciton(int fightAction) = 0;
};
