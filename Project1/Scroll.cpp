#include"Scroll.h"
#include"GameObject.h"
#include <iostream>
using namespace std;

Scroll::Scroll(int row, int col) : GameObject(row, col)
{}

Scroll::~Scroll() {}

bool Scroll::isWeapon()
{
	return false;
}

int Scroll::getdam() { return 0; }
int Scroll::getdext() { return 0; }


Teleportation::Teleportation(int row, int col) : Scroll(row, col)
{

	m_name = "a scroll called scroll of teleportation";

}
string Teleportation::action()
{
	return"You feel your body wrenched in space and time.\n";
}

string Teleportation::name()
{
	return m_name;
}

Armor::Armor(int row, int col) : Scroll(row, col)
{
	m_name = "a scroll called scroll of improve armor";
}
string Armor::action()
{
	return"Your armor glows blue.\n";
}

string Armor::name()
{
	return m_name;
}

Strength::Strength(int row, int col) : Scroll(row, col)
{
	m_name = "a scroll called scroll of raise strength";
}
string Strength::action()
{
	return"Your muscles bulge.\n";
}

string Strength::name()
{
	return m_name;
}

Dexterity::Dexterity(int row, int col) : Scroll(row, col)
{
	m_name = "a scroll called scroll of enhance dexterity";
}
string Dexterity::action()
{
	return"You feel like less of a klutz.\n";
}

string Dexterity::name()
{
	return m_name;
}
Health::Health(int row, int col) :Scroll(row, col)
{
	m_name = "a scroll called scroll of enhance health";
}

string Health::action()
{
	return"You feel your heart beating stronger.\n";
}
string Health::name()
{
	return m_name;
}
