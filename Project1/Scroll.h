#ifndef Scroll_h
#define Scroll_h
#include <iostream>
#include "GameObject.h"

class Scroll :public GameObject
{
public:
	Scroll(int row, int col);
	virtual ~Scroll();

	//Getter
	virtual std::string name() = 0;
	bool isWeapon();
	virtual std::string action() = 0;
	int getdext();
	int getdam();
};

class Teleportation :public Scroll
{
public:
	Teleportation(int row, int col);

	//Getter
	std::string action();
	std::string name();
private:
	std::string m_name;
};

class Armor :public Scroll
{
public:
	Armor(int row, int col);

	//Getter
	std::string action();
	std::string name();
private:
	std::string m_name;

};

class Strength : public Scroll
{
public:
	Strength(int row, int col);

	//Getter
	std::string action();
	std::string name();
private:
	std::string m_name;
};

class Dexterity : public Scroll
{
public:
	Dexterity(int row, int col);

	//Getter
	std::string action();
	std::string name();
private:
	std::string m_name;
};

class Health : public Scroll
{
public:
	Health(int row, int col);

	//Getter
	std::string action();
	std::string name();
private:
	std::string m_name;
};
#endif