#include "Inventory.h"
#include <list>
#include "utilities.h"
#include <vector>
#include "GameObject.h"
#include "Weapon.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

Inventory::Inventory()
{
	string a[1] = { "short sword" };
	x.push_back(*a); //holds the names of each tool
	y.push_back(true); //holds weather each tool is a weapon
	W.push_back(new ShortSword); //create shortSword for player
	msg = "";
	m_size = 1;

}

Inventory::~Inventory()
{
	delete W[0]; //delete short sword
}

void Inventory::display()
{
	clearScreen();
	cout << "Inventory:" << endl;
	string a = "abcdefghijklmnopqrstuvwxyz"; //to output with my tool
	list<string> ::iterator it;
	it = x.begin();
	int i = 0;
	while (it != x.end())
	{
		cout << " " << a[i] << ". " << *it << endl;
		i++;
		it++;
	}
}

void Inventory::add(string toolname, GameObject* tool)
{
	if (toolname[0] == 'a')
		toolname[0] = 'A';
	x.push_back(toolname);
	y.push_back(tool->isWeapon());
	W.push_back(tool);
	m_size++;
}

GameObject* Inventory::wield(GameObject* curr)
{
	string a = "abcdefghijklmnopqrstuvwxyz";
	char temp = getCharacter();//character inputted based on the inventory
	list<string> ::iterator it;
	it = x.begin();
	list<bool>::iterator weap;
	weap = y.begin();
	int i = 0;
	while (it != x.end())
	{
		string s = *it;
		if (a[i] == temp)
		{
			if (*weap) // if picks weapon
			{
				m_wield = true;
				msg = "You are wielding " + *it + "\n";
			}
			else //if picks scroll
			{
				m_wield = false;
				s.erase(0, 16);
				msg = "You can't wield " + s + "\n";
			}
			return *(W.begin() + i);
		}
		weap++;
		it++;
		i++;

	}
	msg = "";
	return curr; //if nothing is picked return the current weapon with no msg
}

GameObject* Inventory::read(GameObject* curr)
{
	string a = "abcdefghijklmnopqrstuvwxyz";
	char temp = getCharacter();//character inputted based on the inventory
	list<string> ::iterator it;
	it = x.begin();
	list<bool>::iterator weap;
	weap = y.begin();
	int i = 0;
	while (it != x.end())
	{
		string s = *it;
		if (a[i] == temp)
		{
			if (!*weap) //if scroll picked
			{
				s.erase(0, 1);
				m_wield = false;
				GameObject* temp = W[i];
				W.erase(W.begin() + i);
				y.erase(weap);
				x.erase(it);
				msg = "You read the" + s;
				m_size--;
				return temp;
			}
			else //if weapon picked
			{
				m_wield = true;
				msg = "You can't read a " + *it;
			}
			return *(W.begin() + i);
		}

		weap++;
		it++;
		i++;
	}
	m_wield = true;
	msg = "";
	return curr; //return current weapon without a msg,so it won't say you can't read it
}

bool Inventory::canWield()
{
	return m_wield;
}

string Inventory::getMsg()
{
	return msg;
}

int Inventory::getSize()
{
	return m_size;
}


GameObject* Inventory::firstweap()
{
	return W[0];
}