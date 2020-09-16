#ifndef Weapon_h
#define Weapon_h
#include "GameObject.h"
#include <string>


class Weapon :public GameObject
{
public:
	//Constructor for weapons already in hand
	Weapon();
	//Constructor for weaps on ground
	Weapon(int row, int col);

	//Getter
	virtual std::string action() = 0;
	virtual int getdext() = 0;
	virtual int getdam() = 0;
	virtual std::string name() = 0;
	bool isWeapon();
};
class ShortSword : public Weapon
{
public:
	ShortSword();
	ShortSword(int row, int col);

	//Getter
	std::string action();
	int getdext();
	int getdam();
	std::string name();
private:
	std::string m_name;

};

class LongSword : public Weapon
{
public:
	LongSword();
	LongSword(int row, int col);

	//Getter
	std::string action();
	int getdext();
	int getdam();
	std::string name();
private:
	std::string m_name;

};

class Mace : public Weapon
{
public:
	Mace(int row, int col);
	std::string action();
	int getdext();
	int getdam();
	std::string name();

private:
	std::string m_name;
};

class MagicAxe : public Weapon
{
public:
	MagicAxe(int row, int col);

	//Getters
	std::string action();
	int getdext();
	int getdam();
	std::string name();

private:
	std::string m_name;
};

class MagicFangs : public Weapon
{
public:
	MagicFangs();
	MagicFangs(int row, int col);

	//Getters
	std::string action();
	int getdext();
	int getdam();
	std::string name();
private:
	std::string m_name;
};
#endif
