#ifndef _PowerEnum_H_
#define _PowerEnum_H_

#define NEWTYPE_ONE "YIN2/YIN (7).png"
#define NEWTYPE_ONE_RECT Rect(0, 0, 57, 68)

#define NEWTYPE_TWO "YIN2/nazi/ER (10).png"
#define NEWTYPE_TWO_RECT Rect(0, 0, 45, 57)

#define NEWTYPE_THREE "YIN2/YIN (7).png"

#define NEWTYPE_ONE_RIGHT   "YIN2/YIN (4).png"
#define NEWTYPE_ONE_LEFT     "YIN2/YIN (6).png"

#define NEWTYPE_TWO_RIGHT  "YIN2/nazi/ER (12).png"
#define NEWTYPE_TWO_LEFT    "YIN2/YIN (7).png"

#define NEWTYPE_TWO_FIGHTONE   "YIN2/nazi/ER (3).png"
#define NEWTYPE_TWO_FIGHTTWO     "YIN2/nazi/ER (4).png"
#define NEWTYPE_TWO_FIGHTTHREE  "YIN2/nazi/ER (5).png"
#define NEWTYPE_TWO_FIGHTFOUR  "YIN2/nazi/ER (6).png"
#define NEWTYPE_TWO_FIGHTFIVE   "YIN2/nazi/ER (7).png"

#define FIRE_MONSTER "FireMonster.png"
#define FIRE_MONSTER_RECT Rect(0, 0, 200, 200)

#define JUMP_MONSTER "mj (1).png"
#define JUMP_MONSTER_RECT Rect(0, 0, 118, 106)

#define BOSS_ONE "boss_ (1).png"
#define BOSS_TWO "Boss/Boss_SP (1).png"

enum PowerEnumStatus
{
	useNone,
	useFire,
	useIce,
	useNewTypeOne,
	useNewTypeTwo,
};

#endif