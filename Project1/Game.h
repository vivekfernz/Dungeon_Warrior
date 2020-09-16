// Game.h

#ifndef GAME_INCLUDED
#define GAME_INCLUDED
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
// You may add data members and other member functions to this class.
class Dungeon;
class Player;
class Inventory;
class Actor;


//For Goblin recursion
class Coord
{
public:
    Coord(int rr, int cc);
    int r() const;
    int c() const;
    void setr(int r);
    void setc(int c);
private:
    int m_row;
    int m_col;
};

class Game
{
public:
    Game(int goblinSmellDistance);
    ~Game();
    void play();
    //Actor Turns
    std::string takePlayerMove();
    std::string takeMonsterMove();
    std::string BogeyMove(Actor* a);
    std::string SnakeMove(Actor* a);
    std::string DragonMove(Actor* a);
    std::string GoblinMove(Actor* a, int n);
    std::string pathExists(Actor* a, Coord point, Coord increment, int n);//recursive function for Goblin move
private:
    std::vector<Dungeon*> dungstorage;
    Player* player;
    Dungeon* m_dungeon;
    Inventory* inventory;
    int m_goblindist;
    std::queue <Coord> goblinCoords;
};


#endif // GAME_INCLUDED

