#include "GameObject.h"
using namespace std;
GameObject::GameObject() {}
GameObject::GameObject(int row, int col)
{
	m_row = row;
	m_col = col;
}

GameObject::~GameObject() {}

int GameObject::getCol()
{
	return m_col;
}

int GameObject::getRow()
{
	return m_row;
}

Trophy::Trophy(int row, int col) :GameObject(row, col) {}
string Trophy::name()
{
	return m_name;
}
bool Trophy::isWeapon()
{
	return false;
}
string Trophy::action()
{
	return "";
}
int Trophy::getdam() { return 0; }
int Trophy::getdext() { return 0; }

Stair::Stair(int row, int col)
{
	m_row = row;
	m_col = col;
}
int Stair::getRow()
{
	return m_row;
}

int Stair::getCol()
{
	return m_col;
}
