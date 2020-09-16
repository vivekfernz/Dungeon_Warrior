#ifndef Inventory_h
#define Inventory_h
#include <iostream>
#include "GameObject.h"
#include <list>
#include <vector>
#include <algorithm>
#include <string>
class Scroll;
class Weapon;
class Inventory {
public:
	Inventory();
	~Inventory();
	void display();

	//Mutator
	void add(std::string toolname, GameObject* tool);

	GameObject* wield(GameObject* curr); //for wielding weaps
	GameObject* read(GameObject* curr); // for reading scrolls

	GameObject* firstweap();//for original short sword

	//Getter
	bool canWield();
	std::string getMsg();
	int getSize();
private:
	std::list<std::string> x;
	std::list<bool> y;
	bool m_wield;
	std::vector<GameObject*> W;
	std::string msg;
	int m_size;


};
#endif