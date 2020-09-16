#ifndef Dungeon_h
#define Dungeon_h
#include <string>
#include <vector>
#include <algorithm>
class Actor;
class Mask;
class Player;
class Stair;
class GameObject;
class Coord;

class Dungeon
{
public:
	Dungeon();
	Dungeon(int level, Player* player);
	~Dungeon();

	//Display function
	void display(std::string msg) const;

	//Room Creation
	void makeRooms(int n);
	bool intersects(int row, int col, int width, int height);
	void makePaths();
	int createMonster();
	int createWeapon();

	//Getters
	int getLevel();
	int getCellStatus(int r, int c);
	Actor* getMonster(int i);
	Player* player()const;
	Mask* mask()const;
	int toolRow(int i);
	int toolCol(int i);
	std::string toolName(int i);
	GameObject* tool(int i);
	int monstCount();

	//Setters
	void setCellStatus(int r, int c, int status);
	void setLevel(int n);





	//Mutator
	void monsterDead(int row, int col);

private:
	int m_rows;
	int m_cols;
	int m_grid[18][70];
	int level;
	Player* m_player;
	Stair* stair;
	std::vector<Actor*> monsters;
	std::vector<GameObject*> tools;
	Mask* m_mask;
	GameObject* trophy;
	int numtools;
	int nummonst;
	struct Room {
	public:
		int x1;
		int x2;
		int y1;
		int y2;
		int centercol;
		int centerrow;
	};
	std::vector<Room> rooms;

};
#endif
