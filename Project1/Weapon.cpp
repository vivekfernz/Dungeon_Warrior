#include "Weapon.h"
#include "Weapon.h"
#include <string>
using namespace std;

//Weapon
Weapon::Weapon() {}
Weapon::Weapon(int row, int col) :GameObject(row, col)
{}

bool Weapon::isWeapon()
{
	return true;
}



//Short sword
ShortSword::ShortSword() : Weapon()
{}
ShortSword::ShortSword(int row, int col) : Weapon(row, col)
{
	m_name = "short sword";
}

string ShortSword::name()
{
	return m_name;
}


string ShortSword::action()
{
	return "slashes short sword";
}

int ShortSword::getdam()
{
	return 2;
}

int ShortSword::getdext()
{
	return 0;
}

//Long sword
LongSword::LongSword() : Weapon()
{}
LongSword::LongSword(int row, int col) : Weapon(row, col)
{
	m_name = "long sword";
}

string LongSword::name()
{
	return m_name;
}

string LongSword::action()
{
	return "swings long sword";
}

int LongSword::getdam()
{
	return 4;
}

int LongSword::getdext()
{
	return 2;
}



//Mace
Mace::Mace(int row, int col) : Weapon(row, col)
{
	{
		m_name = "mace";
	}
}

string Mace::name()
{
	return m_name;
}

string Mace::action()
{
	return "swings mace";
}

int Mace::getdam()
{
	return 2;
}

int Mace::getdext()
{
	return 0;
}

//Magic axe
MagicAxe::MagicAxe(int row, int col) : Weapon(row, col)
{
	m_name = "magic axe";
}

string MagicAxe::name()
{
	return m_name;
}


string MagicAxe::action()
{
	return "chops magic axe";
}

int MagicAxe::getdam()
{
	return 5;
}

int MagicAxe::getdext()
{
	return 5;
}

//Magic Fangs
MagicFangs::MagicFangs() : Weapon() {}
MagicFangs::MagicFangs(int row, int col) : Weapon(row, col)
{
	m_name = "magic fangs of sleep";
}

string MagicFangs::name()
{
	return m_name;
}

string MagicFangs::action()
{
	return "strikes magic fangs";
}

int MagicFangs::getdam()
{
	return 2;
}

int MagicFangs::getdext()
{
	return 3;
}
