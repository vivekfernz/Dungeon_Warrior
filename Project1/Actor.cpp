#include "Actor.h"
#include "utilities.h"
#include "globals.h"
#include "Weapon.h"
#include <string>
using namespace std;
//////////////////////Actor
Actor::Actor(int row, int col)
{
	m_row = row;
	m_col = col;
	m_sleep = 0;
}

Actor::~Actor() {}

int Actor::getRow()
{
	return m_row;
}

int Actor::getCol()
{
	return m_col;
}

void Actor::setRow(int n)
{
	m_row = n;
}

void Actor::setCol(int n)
{
	m_col = n;
}

void Actor::setSleep(int n)
{
	if (n == -1)
		m_sleep--;
	if (n > m_sleep)
		m_sleep = n;
}

int Actor::getSleep()
{
	return m_sleep;
}


//////////Player
Player::Player(int row, int col) :Actor(row, col)
{
	maxhp = 20;
	m_hp = 20;
	m_ap = 2;
	m_sp = 2;
	m_dp = 2;
	m_name = "Player ";
	m_dead = false;
	m_trophy = false;
}

Player::~Player()
{}

void Player::setmaxhp(int n)
{
	maxhp = n;
}
int Player::getmaxhp()
{
	return maxhp;
}

int Player::gethp()
{
	return m_hp;
}

int Player::getap()
{
	return m_ap;
}

int Player::getdp()
{
	return m_dp;
}

int Player::getsp()
{
	return m_sp;
}
void Player::changehp(int n)
{
	if (n == 50) // to cheat
	{
		m_hp = 50;
		return;
	}
	else
	{
		m_hp += n;
	}
	if (m_hp > maxhp)
		m_hp = maxhp;
}

void Player::increasemaxhp()
{
	maxhp += randInt(3, 8);
	if (maxhp > 99)
		maxhp = 99;
}

void Player::increaseap()
{
	m_ap += randInt(1, 3);
	if (m_ap > 99)
		m_ap = 99;
}

void Player::increasesp()
{
	m_sp += randInt(1, 3);
	if (m_sp > 99)
		m_sp = 99;
}

void Player::increasedp()
{
	m_dp++;
	if (m_dp > 99)
		m_dp = 99;
}

GameObject* Player::getWeapon()
{
	return m_weapon;
}

void Player::setWeapon(GameObject* weap)
{
	m_weapon = weap;
}

void Player::setDead()
{
	m_dead = (m_hp <= 0);
}

bool Player::isDead()
{
	return m_dead;
}

void Player::setTrophy(bool result)
{
	m_trophy = result;
}

bool Player::hasTrophy()
{
	return m_trophy;
}

string Player::attack(int target) // uses the weapon action to form full sentence
{
	string targ;
	switch (target)
	{
	case GOBLIN:
		targ = "Goblin ";
		break;
	case DRAGON:
		targ = "Dragon ";
		break;

	case SNAKE:
		targ = "Snakewoman ";
		break;
	case BOGEY:
		targ = "Bogeyman ";
		break;
	}
	string strike = getWeapon()->action();
	return (m_name + strike + " at the " + targ);
}

int Player::attPoints()
{
	return m_dp + getWeapon()->getdext();
}

int Player::defPoints()
{
	return m_ap + m_dp;
}

int Player::damPoints()
{
	return randInt(0, m_sp + getWeapon()->getdam() - 1);
}

string Player::name()
{
	return m_name;
}

void Player::setsp(int n)
{
	m_sp = n;
}

void Player::setCellStatus(int r, int c, int status) {}
int Player::getCellStatus(int r, int c) { return 0; }

//////////////////Goblin

Goblin::Goblin(int row, int col) :Actor(row, col)
{
	m_hp = randInt(15, 20);
	m_ap = 1;
	m_sp = 3;
	m_dp = 1;
	m_name = "the Goblin ";
	m_weapon = new ShortSword;
	m_dead = false;
}

Goblin::~Goblin()
{
	delete m_weapon;
}

int Goblin::gethp()
{
	return m_hp;
}

int Goblin::getap()
{
	return m_ap;
}

int Goblin::getdp()
{
	return m_dp;
}

int Goblin::getsp()
{
	return m_sp;
}
void Goblin::changehp(int n)
{
	m_hp += n;
}

void Goblin::setDead()
{
	m_dead = (m_hp <= 0);
}

bool Goblin::isDead()
{
	return m_dead;
}

GameObject* Goblin::getWeapon()
{
	return m_weapon;
}


string Goblin::attack(int target)// uses the weapon action to form full sentence
{
	if (target != PLAYER)
		return "";
	string targ = " at Player ";
	string strike = getWeapon()->action();
	return (m_name + strike + targ);
}

int Goblin::attPoints()
{
	return m_dp + getWeapon()->getdext();
}

int Goblin::defPoints()
{
	return m_ap + m_dp;
}

int Goblin::damPoints()
{
	return randInt(0, m_sp + getWeapon()->getdam() - 1);
}

string Goblin::name()
{
	return m_name;
}

void Goblin::setCellStatus(int r, int c, int s)
{
	m_grid[r - 1][c - 1] = s;
}

int Goblin::getCellStatus(int r, int c)
{
	return m_grid[r - 1][c - 1];
}

////////Dragon
Dragon::Dragon(int row, int col) :Actor(row, col)
{
	maxhp = randInt(20, 25);
	m_hp = maxhp;
	m_ap = 4;
	m_sp = 4;
	m_dp = 4;
	m_name = "the Dragon ";
	m_weapon = new LongSword;
	m_dead = false;
}

Dragon::~Dragon()
{
	delete m_weapon;
}

int Dragon::gethp()
{
	return m_hp;
}

int Dragon::getap()
{
	return m_ap;
}

int Dragon::getdp()
{
	return m_dp;
}

int Dragon::getsp()
{
	return m_sp;
}
void Dragon::changehp(int n)
{
	m_hp += n;
	if (m_hp > maxhp)
		m_hp = maxhp;
}

void Dragon::setDead()
{
	m_dead = (m_hp <= 0);
}

bool Dragon::isDead()
{
	return m_dead;
}

int Dragon::getmaxhp()
{
	return maxhp;
}

GameObject* Dragon::getWeapon()
{
	return m_weapon;
}

int Dragon::attPoints()
{
	return m_dp + getWeapon()->getdext();
}

int Dragon::defPoints()
{
	return m_ap + m_dp;
}

int Dragon::damPoints()
{
	return randInt(0, m_sp + getWeapon()->getdam() - 1);
}

string Dragon::attack(int target)// uses the weapon action to form full sentence
{
	if (target != PLAYER)
		return "";
	string targ = " at Player ";
	string strike = getWeapon()->action();
	return m_name + strike + targ;
}

string Dragon::name()
{
	return m_name;
}

void Dragon::setCellStatus(int r, int c, int status) {}
int Dragon::getCellStatus(int r, int c) { return 0; }

/////////////////////SnakeWoman
SnakeWoman::SnakeWoman(int row, int col) :Actor(row, col)
{
	m_hp = randInt(15, 20);
	m_ap = 3;
	m_sp = 2;
	m_dp = 3;
	m_name = "the Snakewoman ";
	m_weapon = new MagicFangs;
	m_dead = false;
}

SnakeWoman::~SnakeWoman()
{
	delete m_weapon;
}

int SnakeWoman::gethp()
{
	return m_hp;
}

int SnakeWoman::getap()
{
	return m_ap;
}

int SnakeWoman::getdp()
{
	return m_dp;
}

int SnakeWoman::getsp()
{
	return m_sp;
}
void SnakeWoman::changehp(int n)
{
	m_hp += n;
}

void SnakeWoman::setDead()
{
	m_dead = (m_hp <= 0);
}

bool SnakeWoman::isDead()
{
	return m_dead;
}

GameObject* SnakeWoman::getWeapon()
{
	return m_weapon;
}


string SnakeWoman::attack(int target)// uses the weapon action to form full sentence
{
	if (target != PLAYER)
		return "";
	string targ = " at Player ";
	string strike = getWeapon()->action();
	return m_name + strike + targ;
}

int SnakeWoman::attPoints()
{
	return m_dp + getWeapon()->getdext();
}

int SnakeWoman::defPoints()
{
	return m_ap + m_dp;
}

int SnakeWoman::damPoints()
{
	return randInt(0, m_sp + getWeapon()->getdam() - 1);
}

string SnakeWoman::name()
{
	return m_name;
}

void SnakeWoman::setCellStatus(int r, int c, int status) {}
int SnakeWoman::getCellStatus(int r, int c) { return 0; }

/////////////////Bogey
Bogey::Bogey(int row, int col) :Actor(row, col)
{
	m_hp = randInt(15, 20);
	m_ap = 2;
	m_sp = randInt(2, 3);
	m_dp = randInt(2, 3);
	m_name = "the Bogeyman ";
	m_weapon = new ShortSword;
	m_dead = false;
}

Bogey::~Bogey()
{
	delete m_weapon;
}

int Bogey::gethp()
{
	return m_hp;
}

int Bogey::getap()
{
	return m_ap;
}

int Bogey::getdp()
{
	return m_dp;
}

int Bogey::getsp()
{
	return m_sp;
}
void Bogey::changehp(int n)
{
	m_hp += n;
}

void Bogey::setDead()
{
	m_dead = (m_hp <= 0);
}

bool Bogey::isDead()
{
	return m_dead;
}

GameObject* Bogey::getWeapon()
{
	return m_weapon;
}

string Bogey::attack(int target)// uses the weapon action to form full sentence
{
	if (target != PLAYER)
		return "";
	string targ = " at Player ";
	string strike = getWeapon()->action();
	return m_name + strike + targ;
}

int Bogey::attPoints()
{
	return m_dp + getWeapon()->getdext();
}

int Bogey::defPoints()
{
	return m_ap + m_dp;
}

int Bogey::damPoints()
{
	return randInt(0, m_sp + getWeapon()->getdam() - 1);
}

string Bogey::name()
{
	return m_name;
}

void Bogey::setCellStatus(int r, int c, int status) {}
int Bogey::getCellStatus(int r, int c) { return 0; }