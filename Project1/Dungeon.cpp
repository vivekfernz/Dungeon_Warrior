#include "Dungeon.h"
#include "Actor.h"
#include "utilities.h"
#include "globals.h"
#include "Weapon.h"
#include "GameObject.h"
#include "Scroll.h"
#include "Mask.h"
#include <vector>
#include <algorithm>
#include <iostream>;
using namespace std;

Dungeon::Dungeon()//lvl 0
{
	m_mask = new Mask;
	m_rows = 18;
	m_cols = 70;
	level = 0;
	//////MAKE WALLS 
	for (int r = 1; r <= m_rows; r++)
	{
		for (int c = 1; c <= m_cols; c++)
		{
			m_grid[r - 1][c - 1] = WALL;
		}
	}
	///MAKE ROOMS
	int numberRooms = randInt(7, 10);
	makeRooms(numberRooms);
	makePaths();
	int randrow = randInt(2, m_rows - 1);
	int randcol = randInt(2, m_cols - 1);
	while (m_grid[randrow - 1][randcol - 1] != PLAYER)
	{

		if (m_grid[randrow - 1][randcol - 1] == EMPTY)
		{
			m_player = new Player(randrow, randcol);
			m_grid[randrow - 1][randcol - 1] = PLAYER;
		}
		else
		{
			randrow = randInt(2, m_rows - 1);
			randcol = randInt(2, m_cols - 1);
		}
	}
	/////STAIRS
	randrow = randInt(2, m_rows - 1);
	randcol = randInt(2, m_cols - 1);
	while (m_mask->getCellStatus(randrow, randcol) != STAIR)
	{
		if (m_grid[randrow - 1][randcol - 1] != WALL && m_mask->getCellStatus(randrow, randcol) != WEAPON && m_mask->getCellStatus(randrow, randcol) != TROPHY && m_mask->getCellStatus(randrow, randcol) != SCROLL)
		{
			stair = new Stair(randrow, randcol);
			m_mask->setCellStatus(randrow, randcol, STAIR);
		}
		else
		{
			randrow = randInt(2, m_rows - 1);
			randcol = randInt(2, m_cols - 1);
		}
	}

	////WEAPONS
	numtools = randInt(2, 3);
	GameObject* temp;
	int i = 0;
	for (i; i < numtools; i++)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_mask->getCellStatus(randrow, randcol) != WEAPON && m_mask->getCellStatus(randrow, randcol) != SCROLL)
		{
			if (m_grid[randrow - 1][randcol - 1] != WALL && m_mask->getCellStatus(randrow, randcol) != STAIR && m_mask->getCellStatus(randrow, randcol) != TROPHY)
			{
				int obj = randInt(1, 2);
				if (obj == 1)
				{
					int weap = randInt(1, 3);
					switch (weap)
					{
					case 1:
						temp = new ShortSword(randrow, randcol);
						break;
					case 2:
						temp = new LongSword(randrow, randcol);
						break;
					case 3:
						temp = new Mace(randrow, randcol);
						break;
					}
					tools.push_back(temp);
					m_mask->setCellStatus(randrow, randcol, WEAPON);
				}
				else
				{
					int scrolltype = randInt(1, 4);
					switch (scrolltype)
					{
					case 1:
						temp = new Armor(randrow, randcol);
						break;
					case 2:
						temp = new Strength(randrow, randcol);
						break;
					case 3:
						temp = new Dexterity(randrow, randcol);
						break;
					case 4:
						temp = new Health(randrow, randcol);
						break;
					}
					tools.push_back(temp);
					m_mask->setCellStatus(randrow, randcol, SCROLL);
				}
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}
	////MONSTERS
	nummonst = randInt(2, 5 * (level + 1) + 1);
	Actor* tempmonst;
	for (int i = 0; i < nummonst; i++)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_grid[randrow - 1][randcol - 1] != GOBLIN && m_grid[randrow - 1][randcol - 1] != SNAKE && m_grid[randrow - 1][randcol - 1] != DRAGON && m_grid[randrow - 1][randcol - 1] != BOGEY)
		{


			if (m_grid[randrow - 1][randcol - 1] == EMPTY)
			{
				switch (createMonster())
				{
				case 1:
					tempmonst = new Goblin(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = GOBLIN;
					break;
				case 2:
					tempmonst = new SnakeWoman(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = SNAKE;
					break;
				}
				monsters.push_back(tempmonst);
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}
}
Dungeon::Dungeon(int lev, Player* player)//Every other level to carry player over
{
	m_mask = new Mask;
	m_rows = 18;
	m_cols = 70;
	level = lev;
	//////MAKE WALLS 
	for (int r = 1; r <= m_rows; r++)
	{
		for (int c = 1; c <= m_cols; c++)
		{
			m_grid[r - 1][c - 1] = WALL;
		}
	}

	///MAKE ROOMS
	int numberRooms = randInt(7, 10);
	makeRooms(numberRooms);
	makePaths();
	int randrow = randInt(2, m_rows - 1);
	int randcol = randInt(2, m_cols - 1);
	while (m_grid[randrow - 1][randcol - 1] != PLAYER)
	{

		if (m_grid[randrow - 1][randcol - 1] == EMPTY)
		{
			m_player = player;
			m_player->setRow(randrow);
			m_player->setCol(randcol);
			m_grid[randrow - 1][randcol - 1] = PLAYER;
		}
		else
		{
			randrow = randInt(2, m_rows - 1);
			randcol = randInt(2, m_cols - 1);
		}
	}

	/////STAIRS
	if (level != 4)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_mask->getCellStatus(randrow, randcol) != STAIR)
		{
			if (m_grid[randrow - 1][randcol - 1] != WALL && m_mask->getCellStatus(randrow, randcol) != WEAPON && m_mask->getCellStatus(randrow, randcol) != TROPHY && m_mask->getCellStatus(randrow, randcol) != SCROLL)
			{
				stair = new Stair(randrow, randcol);
				m_mask->setCellStatus(randrow, randcol, STAIR);
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}
	////WEAPONS
	numtools = randInt(2, 3);
	int i = 0;
	GameObject* temp;
	for (i; i < numtools; i++)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_mask->getCellStatus(randrow, randcol) != WEAPON && m_mask->getCellStatus(randrow, randcol) != SCROLL)
		{
			if (m_grid[randrow - 1][randcol - 1] != WALL && m_mask->getCellStatus(randrow, randcol) != STAIR && m_mask->getCellStatus(randrow, randcol) != TROPHY)
			{
				int obj = randInt(1, 2);
				if (obj == 1)
				{
					int weap = randInt(1, 3);
					switch (weap)
					{
					case 1:
						temp = new ShortSword(randrow, randcol);
						break;
					case 2:
						temp = new LongSword(randrow, randcol);
						break;
					case 3:
						temp = new Mace(randrow, randcol);
						break;
					}
					tools.push_back(temp);
					m_mask->setCellStatus(randrow, randcol, WEAPON);
				}
				else
				{
					int scrolltype = randInt(1, 4);
					switch (scrolltype)
					{
					case 1:
						temp = new Armor(randrow, randcol);
						break;
					case 2:
						temp = new Strength(randrow, randcol);
						break;
					case 3:
						temp = new Dexterity(randrow, randcol);
						break;
					case 4:
						temp = new Health(randrow, randcol);
						break;
					}
					tools.push_back(temp);
					m_mask->setCellStatus(randrow, randcol, SCROLL);
				}
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}

	///TROPHY
	if (level == 4)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_mask->getCellStatus(randrow, randcol) != TROPHY)
		{
			if (m_grid[randrow - 1][randcol - 1] != WALL && m_mask->getCellStatus(randrow, randcol) != WEAPON && m_mask->getCellStatus(randrow, randcol) != STAIR && m_mask->getCellStatus(randrow, randcol) != SCROLL)
			{
				trophy = new Trophy(randrow, randcol);
				m_mask->setCellStatus(randrow, randcol, TROPHY);
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}
	////MONSTERS
	nummonst = randInt(2, 5 * (level + 1) + 1);
	Actor* tempmonst;
	for (int i = 0; i < nummonst; i++)
	{
		randrow = randInt(2, m_rows - 1);
		randcol = randInt(2, m_cols - 1);
		while (m_grid[randrow - 1][randcol - 1] != GOBLIN && m_grid[randrow - 1][randcol - 1] != SNAKE && m_grid[randrow - 1][randcol - 1] != DRAGON && m_grid[randrow - 1][randcol - 1] != BOGEY)
		{


			if (m_grid[randrow - 1][randcol - 1] == EMPTY)
			{
				switch (createMonster())
				{
				case 1:
					tempmonst = new Goblin(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = GOBLIN;
					break;
				case 2:
					tempmonst = new SnakeWoman(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = SNAKE;
					break;
				case 3:
					tempmonst = new Bogey(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = BOGEY;
					break;
				case 4:
					tempmonst = new Dragon(randrow, randcol);
					m_grid[randrow - 1][randcol - 1] = DRAGON;
					break;
				}
				monsters.push_back(tempmonst);
			}
			else
			{
				randrow = randInt(2, m_rows - 1);
				randcol = randInt(2, m_cols - 1);
			}
		}
	}
}

Dungeon::~Dungeon()
{
	delete m_mask;
	delete stair;
	while (!rooms.empty())
		rooms.erase(rooms.begin());
	if (level == 4)//only last level has trophy
	{
		delete trophy;
	}
	while (!tools.empty())
	{
		delete tools[0];
		tools.erase(tools.begin());
	}
	while (!monsters.empty())
	{
		delete monsters[0];
		monsters.erase(monsters.begin());
	}
}

void Dungeon::display(string msg) const
{
	char displayGrid[18][70];
	int r, c;
	for (r = 1; r <= m_rows; r++)
	{
		for (c = 1; c <= m_cols; c++)
		{
			switch (m_mask->getCellStatus(r, c))
			{
			case STAIR:
				displayGrid[r - 1][c - 1] = '>';
				break;
			case WEAPON:
				displayGrid[r - 1][c - 1] = ')';
				break;
			case TROPHY:
				displayGrid[r - 1][c - 1] = '&';
				break;
			case SCROLL:
				displayGrid[r - 1][c - 1] = '?';
				break;
			default:
				break;
			}
			switch (m_grid[r - 1][c - 1])
			{
			case (EMPTY):
				if (m_mask->getCellStatus(r, c) == WALL)
					displayGrid[r - 1][c - 1] = ' ';
				break;
			case(WALL):
				displayGrid[r - 1][c - 1] = '#';
				break;
			case (PLAYER):
				displayGrid[r - 1][c - 1] = '@';
				break;
			case(GOBLIN):
				displayGrid[r - 1][c - 1] = 'G';
				break;
			case(SNAKE):
				displayGrid[r - 1][c - 1] = 'S';
				break;
			case(BOGEY):
				displayGrid[r - 1][c - 1] = 'B';
				break;
			case(DRAGON):
				displayGrid[r - 1][c - 1] = 'D';
				break;
			default:
				break;
			}
		}
	}
	clearScreen();
	for (r = 1; r <= m_rows; r++)
	{
		for (c = 1; c <= m_cols; c++)
		{
			cout << displayGrid[r - 1][c - 1];
		}
		cout << endl;
	}
	cout << "Dungeon Level: " << level;
	cout << ", Hit Points: " << m_player->gethp();
	cout << ", Armor: " << m_player->getap();
	cout << ", Strength: " << m_player->getsp();
	cout << ", Dexterity: " << m_player->getdp() << endl << endl;
	cout << msg;
}

void Dungeon::makeRooms(int n)
{

	for (int i = 0; i < n; i++)
	{

		int startrow = randInt(2, 12);
		int startcol = randInt(2, 63);
		int width = randInt(5, 60 / n);
		int height = randInt(5, 9);
		//check for overlap
		if (!intersects(startrow, startcol, width, height))
		{
			int endcol = startcol + width;
			int endrow = startrow + height;
			for (int k = 0; k < height; k++)
			{
				for (int j = 0; j < width; j++)
				{
					m_grid[startrow + k - 1][startcol + j - 1] = EMPTY;
				}
			}
			Room a = {};
			a.x1 = startcol;
			a.x2 = endcol;
			a.y1 = startrow;
			a.y2 = endrow;
			a.centercol = (startcol + endcol) / 2;
			a.centerrow = (startrow + endrow) / 2;
			rooms.push_back(a);
			//sort rooms from left to right
			sort(rooms.begin(), rooms.end(), [](const Room& lhs, const Room& rhs)
				{
					return lhs.x1 < rhs.x1;
				});
		}
	}
}

bool Dungeon::intersects(int row, int col, int width, int height)
{
	//checks overlap and checks one beyond in each direction to have walls between
	for (int i = -1; i <= height + 1; i++)
		for (int j = -1; j <= width + 1; j++)
		{
			if (row + i - 1 >= 17 || col + j - 1 >= 70 || row + i - 1 <= 0 || col + j - 1 <= 0)
				return true;
			if (m_grid[row + i - 1][col + j - 1] == EMPTY)
				return true;
		}
	//if no overlap
	return false;
}

void Dungeon::makePaths()
{	//corridors
	for (size_t i = 0; i < rooms.size() - 1; i++)
	{
		if (i == rooms.size())
			break;
		int col1 = rooms[i].centercol;
		int row1 = rooms[i].centerrow;

		//Create a path horizontally
		while (col1 != rooms[i + 1].centercol)
		{
			m_grid[row1 - 1][col1 - 1] = EMPTY;
			col1++;
		}

		//Connect the path vertically
		while (row1 != rooms[i + 1].centerrow)
		{
			m_grid[row1 - 1][col1 - 1] = EMPTY;
			if (row1 < rooms[i + 1].centerrow)
				row1++;
			else
				row1--;
		}

	}
}

int Dungeon::getLevel()
{
	return level;
}

void Dungeon::setLevel(int n)
{
	level = n;
}

Player* Dungeon::player() const
{
	return m_player;
}

int Dungeon::getCellStatus(int r, int c)
{
	return m_grid[r - 1][c - 1];
}

void Dungeon::setCellStatus(int r, int c, int status)
{
	m_grid[r - 1][c - 1] = status;
}

int Dungeon::createMonster()
{
	//return number based on level;
	int monst;
	switch (level)
	{
	case 0:
	case 1:
		monst = randInt(1, 2);
		break;
	case 2:
		monst = randInt(1, 3);
		break;
	case 3:
	case 4:
		monst = randInt(1, 4);
		break;
	}
	return monst;
}
Mask* Dungeon::mask() const
{
	return m_mask;
}

int Dungeon::toolRow(int i)
{

	return tools[i]->getRow();
}

int Dungeon::toolCol(int i)
{
	return tools[i]->getCol();
}

string Dungeon::toolName(int i)
{
	return tools[i]->name();
}

GameObject* Dungeon::tool(int i)
{
	return tools[i];
}

Actor* Dungeon::getMonster(int i)
{
	return monsters[i];
}

void Dungeon::monsterDead(int row, int col)
{

	GameObject* temp;
	for (int i = 0; i < monstCount(); i++)
	{
		//delete dead monster from vector
		if (monsters[i]->getRow() == row && monsters[i]->getCol() == col)
		{
			delete monsters[i];
			monsters.erase(monsters.begin() + i);
			nummonst--;
			break;
		}
	}
	switch (getCellStatus(row, col))
	{
		//drop a weapon chance
	case GOBLIN:
		if (m_mask->getCellStatus(row, col) == WALL)
		{
			if (trueWithProbability(1.0 / 3))
			{

				m_mask->setCellStatus(row, col, WEAPON);
				if (trueWithProbability(1.0 / 2))
				{
					temp = new MagicAxe(row, col);
					tools.push_back(temp);

				}
				else
				{
					temp = new MagicFangs(row, col);
					tools.push_back(temp);

				}
			}
		}
		break;
	case SNAKE:
		if (m_mask->getCellStatus(row, col) == WALL)
			if (trueWithProbability(1.0 / 3))
			{
				m_mask->setCellStatus(row, col, WEAPON);
				temp = new MagicFangs(row, col);
				tools.push_back(temp);

			}
		break;
	case BOGEY:
		if (m_mask->getCellStatus(row, col) == WALL)
			if (trueWithProbability(1.0 / 10))
			{
				m_mask->setCellStatus(row, col, WEAPON);
				temp = new MagicAxe(row, col);
				tools.push_back(temp);

			}
		break;
	case DRAGON:
		if (m_mask->getCellStatus(row, col) == WALL)
		{
			m_mask->setCellStatus(row, col, SCROLL);
			switch (randInt(1, 5))
			{
			case 1:
				temp = new Health(row, col);
				break;
			case 2:
				temp = new Strength(row, col);
				break;
			case 3:
				temp = new Dexterity(row, col);
				break;
			case 4:
				temp = new Armor(row, col);
				break;
			case 5:
				temp = new Teleportation(row, col);
				break;
			}
			tools.push_back(temp);

		}
		break;
	}
	setCellStatus(row, col, EMPTY);
}

int Dungeon::monstCount()
{
	return monsters.size();
}