// Game.cpp
#include<stdlib.h>
#include "Game.h"
#include "utilities.h"
#include "globals.h"
#include "Dungeon.h"
#include "GameObject.h"
#include "Inventory.h"
#include "Weapon.h"
#include "Actor.h"
#include "Mask.h"
#include <queue>
#include <iostream>
#include <cmath>
using namespace std;

// Implement these and other Game member functions you may have added.

//recursive function to find shortest path and return direction for Goblin to move
string Game::pathExists(Actor* a, Coord b, Coord increment, int n)
{
    int count = 0;
    goblinCoords.pop();
    int r = b.r();
    int c = b.c();
    if (r == increment.r() && c == increment.c()) //coordinate for when to increment is reached
        n--;
    Coord i(increment.r(), increment.c());
    if (n < 0)
        return "";
    if (abs(a->getRow() - player->getRow()) + abs(a->getCol() - player->getCol()) > 15)
        return "";

    a->setCellStatus(r, c, WALL);

    //North
    if (a->getCellStatus(r - 1, c) == EMPTY || a->getRow() == r - 1 && a->getCol() == c)
    {
        if (r - 1 == a->getRow() && c == a->getCol())
        {
            return "down";
        }
        a->setCellStatus(r - 1, c, WALL);
        Coord d(r - 1, c);
        goblinCoords.push(d);
        count++;
        if (r == increment.r() && c == increment.c() && count == 1)
        {
            i.setr(d.r());
            i.setc(d.c());
        }
    }

    //East
    if (a->getCellStatus(r, c + 1) == EMPTY || a->getRow() == r && a->getCol() == c + 1)
    {
        if (r == a->getRow() && c + 1 == a->getCol())
        {
            return "left";
        }
        a->setCellStatus(r, c + 1, WALL);
        Coord d(r, c + 1);
        goblinCoords.push(d);
        count++;
        if (b.r() == increment.r() && b.c() == increment.c() && count == 1)
        {
            i.setr(d.r());
            i.setc(d.c());
        }
    }

    //South
    if (a->getCellStatus(r + 1, c) == EMPTY || a->getRow() == r + 1 && a->getCol() == c)
    {

        if (r + 1 == a->getRow() && c == a->getCol())
        {
            return "up";
        }
        a->setCellStatus(r + 1, c, WALL);
        Coord d(r + 1, c);
        goblinCoords.push(d);
        count++;
        if (b.r() == increment.r() && b.c() == increment.c() && count == 1)
        {
            i.setr(d.r());
            i.setc(d.c());
        }
    }

    //West
    if (a->getCellStatus(r, c - 1) == EMPTY || a->getRow() == r && a->getCol() == c - 1)
    {

        if (r == a->getRow() && c - 1 == a->getCol())
        {
            return "right";
        }
        a->setCellStatus(r, c - 1, WALL);
        Coord d(r, c - 1);
        goblinCoords.push(d);
        count++;
        if (b.r() == increment.r() && b.c() == increment.c() && count == 1)
        {
            i.setr(d.r());
            i.setc(d.c());
        }
    }
    if (goblinCoords.empty())
        return"";
    return pathExists(a, goblinCoords.front(), i, n);
}

//Coordinate class for goblin
Coord::Coord(int r, int c) :m_row(r), m_col(c)
{}
int Coord::r() const { return m_row; }
int Coord::c() const { return m_col; }
void Coord::setr(int r) { m_row = r; }
void Coord::setc(int c) { m_col = c; }


Game::Game(int goblinSmellDistance)
{
    m_dungeon = new Dungeon;
    dungstorage.push_back(m_dungeon);
    inventory = new Inventory;
    m_dungeon->player()->setWeapon(inventory->firstweap());//give the shortSword to the player
    m_goblindist = goblinSmellDistance;
}
Game::~Game()
{
    size_t i = 0;
    while (i < dungstorage.size())
    {
        delete dungstorage[0];
        dungstorage.erase(dungstorage.begin());
    }
    delete player;
    delete inventory;
}
void Game::play()
{
    player = m_dungeon->player();
    m_dungeon->display("");


    while (!player->isDead() && !player->hasTrophy())//til game ends
    {
        string msg = takePlayerMove();
        if (msg == "quit") //quit the game
            break;
        if (msg == "new level" || msg == "You pick up the golden idol \nCongratulations, you won!\n")
        {

            msg = "";
            m_dungeon = new Dungeon(m_dungeon->getLevel() + 1, m_dungeon->player());
            dungstorage.push_back(m_dungeon);
        }
        else
        {
            msg += takeMonsterMove();
        }
        m_dungeon->display(msg);

    }

    if (player->isDead() || player->hasTrophy())
    {
        cout << "Press q to exit game." << endl;
        while (getCharacter() != 'q');
    }

}


string Game::takePlayerMove()
{
    player = m_dungeon->player();
    Mask* mask = m_dungeon->mask();
    GameObject* temp;
    string attack = "";
    string msg = "";
    Actor* tempMonst;
    if (trueWithProbability(0.1))//regain hp maybe
    {
        player->changehp(1);
    }
    if (player->getSleep() != 0)//if asleep
    {
        getCharacter();
        player->setSleep(-1);
        return"";
    }
    switch (getCharacter())
    {
    case ARROW_DOWN:
        if (m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), EMPTY);
            player->setRow(player->getRow() + 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), PLAYER);
        }
        else if (m_dungeon->getCellStatus(player->getRow() + 1, player->getCol()) != WALL)//attack
        {
            msg = (player->attack(m_dungeon->getCellStatus(player->getRow() + 1, player->getCol())));
            int i = 0;
            while (m_dungeon->getMonster(i)->getRow() != player->getRow() + 1 || m_dungeon->getMonster(i)->getCol() != player->getCol())
            {
                i++;
                if (i == m_dungeon->monstCount())
                    break;
            }
            tempMonst = m_dungeon->getMonster(i);
            if (randInt(1, tempMonst->defPoints()) > randInt(1, player->attPoints()))
                attack = "and misses.\n";
            else
            {
                attack = "and hits.\n";
                tempMonst->changehp(-player->damPoints());
                if (tempMonst->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    m_dungeon->monsterDead(tempMonst->getRow(), tempMonst->getCol());
                }
                else if (player->getWeapon()->name() == "magic fangs of sleep")// sleep chance
                {
                    if (trueWithProbability(1.0 / 5))
                    {
                        tempMonst->setSleep(randInt(2, 6));
                        attack = "hits, putting " + m_dungeon->getMonster(i)->name() + "to sleep.\n";
                    }
                }
            }
        }
        return msg + attack;
        break;
    case ARROW_LEFT:
        if (m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) == EMPTY) //movement
        {
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), EMPTY);
            player->setCol(player->getCol() - 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), PLAYER);
        }
        else if (m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1) != WALL)//attack
        {
            msg = (player->attack(m_dungeon->getCellStatus(player->getRow(), player->getCol() - 1)));
            int i = 0;
            while (m_dungeon->getMonster(i)->getRow() != player->getRow() || m_dungeon->getMonster(i)->getCol() != player->getCol() - 1)
                i++;
            tempMonst = m_dungeon->getMonster(i);
            if (randInt(1, tempMonst->defPoints()) > randInt(1, player->attPoints()))
                attack = "and misses.\n";
            else
            {
                attack = "and hits.\n";
                tempMonst->changehp(-player->damPoints());
                if (tempMonst->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    m_dungeon->monsterDead(tempMonst->getRow(), tempMonst->getCol());
                }
                else if (player->getWeapon()->name() == "magic fangs of sleep")// sleep chance
                {
                    if (trueWithProbability(1.0 / 5))
                    {
                        tempMonst->setSleep(randInt(2, 6));
                        attack = "hits, putting " + m_dungeon->getMonster(i)->name() + "to sleep.\n";
                    }
                }
            }
        }
        return msg + attack;
        break;
    case ARROW_RIGHT:
        if (m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), EMPTY);
            player->setCol(player->getCol() + 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), PLAYER);
        }
        else if (m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1) != WALL)//attack
        {
            msg = (player->attack(m_dungeon->getCellStatus(player->getRow(), player->getCol() + 1)));
            int i = 0;
            while (m_dungeon->getMonster(i)->getRow() != player->getRow() || m_dungeon->getMonster(i)->getCol() != player->getCol() + 1)
                i++;
            tempMonst = m_dungeon->getMonster(i);
            if (randInt(1, tempMonst->defPoints()) > randInt(1, player->attPoints()))
                attack = "and misses.\n";
            else
            {
                attack = "and hits.\n";
                tempMonst->changehp(-player->damPoints());
                if (tempMonst->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    m_dungeon->monsterDead(tempMonst->getRow(), m_dungeon->getMonster(i)->getCol());
                }
                else if (player->getWeapon()->name() == "magic fangs of sleep")// sleep chance
                {
                    if (trueWithProbability(1.0 / 5))
                    {
                        tempMonst->setSleep(randInt(2, 6));
                        attack = "hits, putting " + m_dungeon->getMonster(i)->name() + "to sleep.\n";
                    }
                }
            }
        }
        return msg + attack;
        break;

    case ARROW_UP:
        if (m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), EMPTY);
            player->setRow(player->getRow() - 1);
            m_dungeon->setCellStatus(player->getRow(), player->getCol(), PLAYER);
        }
        else if (m_dungeon->getCellStatus(player->getRow() - 1, player->getCol()) != WALL)//attack
        {
            msg = (player->attack(m_dungeon->getCellStatus(player->getRow() - 1, player->getCol())));
            int i = 0;
            while (m_dungeon->getMonster(i)->getRow() != player->getRow() - 1 || m_dungeon->getMonster(i)->getCol() != player->getCol())
                i++;
            tempMonst = m_dungeon->getMonster(i);
            if (randInt(1, tempMonst->defPoints()) > randInt(1, player->attPoints()))
                attack = "and misses.\n";
            else
            {
                attack = "and hits.\n";
                tempMonst->changehp(-player->damPoints());
                if (tempMonst->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    m_dungeon->monsterDead(tempMonst->getRow(), m_dungeon->getMonster(i)->getCol());
                }
                else if (player->getWeapon()->name() == "magic fangs of sleep") // sleep chance
                {
                    if (trueWithProbability(1.0 / 5))
                    {
                        tempMonst->setSleep(randInt(2, 6));
                        attack = "hits, putting " + m_dungeon->getMonster(i)->name() + "to sleep.\n";
                    }
                }
            }
        }
        return msg + attack;
        break;
    case '>':
        if (mask->getCellStatus(player->getRow(), player->getCol()) == STAIR)
            return "new level";
        break;
    case 'g': //pickup
        if (mask->getCellStatus(player->getRow(), player->getCol()) == TROPHY)
        {
            player->setTrophy(true);
            return"You pick up the golden idol \nCongratulations, you won!\n";
        }
        else if (mask->getCellStatus(player->getRow(), player->getCol()) == WEAPON || mask->getCellStatus(player->getRow(), player->getCol()) == SCROLL)
        {
            if (inventory->getSize() >= 26)
                return "Your knapsack is full; you can't pick that up.\n";
            int i = 0;
            while (m_dungeon->toolRow(i) != player->getRow() || m_dungeon->toolCol(i) != player->getCol())
            {
                i++;
            }
            mask->setCellStatus(player->getRow(), player->getCol(), WALL);
            inventory->add(m_dungeon->toolName(i), m_dungeon->tool(i));
            return "You pick up " + m_dungeon->toolName(i) + "\n";
        }
        return "";
        break;
    case 'w': //wield weapon
        inventory->display();
        temp = inventory->wield(player->getWeapon());
        if (inventory->canWield())
        {
            player->setWeapon(temp);
        }
        return inventory->getMsg();
        break;
    case 'r': //read scroll
        inventory->display();
        temp = inventory->read(player->getWeapon());
        if (!inventory->canWield())
        {

            msg = temp->action();
            if (temp->name() == "a scroll called scroll of improve armor")
            {
                player->increaseap();
            }
            else if (temp->name() == "a scroll called scroll of teleportation")
            {
                int row = player->getRow();
                int col = player->getCol();
                while (m_dungeon->getCellStatus(player->getRow(), player->getCol()) != EMPTY) //loop til u find an empty spot
                {
                    player->setRow(randInt(2, 17));
                    player->setCol(randInt(2, 69));
                }
                m_dungeon->setCellStatus(player->getRow(), player->getCol(), PLAYER);
                m_dungeon->setCellStatus(row, col, EMPTY);
            }
            else if (temp->name() == "a scroll called scroll of raise strength")
                player->increasesp();
            else if (temp->name() == "a scroll called scroll of enhance dexterity")
                player->increasedp();
            else if (temp->name() == "a scroll called scroll of enhance health")
                player->increasemaxhp();
            return inventory->getMsg() + "\n" + msg;
        }
        if (inventory->getMsg() == "")
            return inventory->getMsg();
        else
            return inventory->getMsg() + "\n";
    case 'i':
        inventory->display();
        getCharacter();
        return "";
        break;
    case 'c':
        player->setmaxhp(50);
        player->changehp(50);
        player->setsp(9);
        break;
    case 'q':
        return "quit";
    default:
        return "";
        break;
    }
    return "";
}


string Game::takeMonsterMove()
{
    string msg = "";
    int i = 0;
    while (i < m_dungeon->monstCount())//go thru all monsters
    {
        Actor* tempMonst = m_dungeon->getMonster(i);
        if (m_dungeon->getCellStatus(tempMonst->getRow(), tempMonst->getCol()) == BOGEY)
        {
            msg += BogeyMove(tempMonst);
        }
        if (m_dungeon->getCellStatus(tempMonst->getRow(), tempMonst->getCol()) == SNAKE)
        {
            msg += SnakeMove(tempMonst);
        }
        if (m_dungeon->getCellStatus(tempMonst->getRow(), tempMonst->getCol()) == DRAGON)
        {
            msg += DragonMove(tempMonst);
        }
        if (m_dungeon->getCellStatus(tempMonst->getRow(), tempMonst->getCol()) == GOBLIN)
        {
            //set up grid for goblin that mirrors the dungeon grid, but can be changed without changing dungeon
            for (int i = 1; i <= 18; i++)
                for (int j = 1; j <= 70; j++)
                    tempMonst->setCellStatus(i, j, m_dungeon->getCellStatus(i, j));
            msg += GoblinMove(tempMonst, m_goblindist);
        }
        i++;
    }
    return msg;

}


string Game::BogeyMove(Actor* a)
{
    if (a->getSleep() != 0)
    {
        a->setSleep(-1);
        return "";
    }
    string attack = "";
    bool rowDir = abs(a->getRow() + 1 - player->getRow()) > abs(a->getRow() - 1 - player->getRow());//find which way to move vertically
    bool colDir = abs(a->getCol() + 1 - player->getCol()) > abs(a->getCol() - 1 - player->getCol());//find which way to mov horizontally
    if (abs(a->getRow() - player->getRow()) + abs(a->getCol() - player->getCol()) > 5)//if in range
    {
        return"";
    }
    else
    {
        if (a->getRow() == player->getRow()) //if in same row move cols
        {
            if (colDir)
                if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == EMPTY)//movement
                {

                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow(), a->getCol() - 1, BOGEY);
                    a->setCol(a->getCol() - 1);
                    return "";
                }
                else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == PLAYER)//attack
                {
                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {
                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return "";
                }
            else
            {
                if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == EMPTY)//movement
                {

                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow(), a->getCol() + 1, BOGEY);
                    a->setCol(a->getCol() + 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == PLAYER)//attack
                {

                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {

                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return"";
                }
            }
        }
        else if (a->getCol() == player->getCol()) //cols are same
        {
            if (rowDir)
                if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == EMPTY)//movement
                {
                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow() - 1, a->getCol(), BOGEY);
                    a->setRow(a->getRow() - 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == PLAYER)//attack
                {

                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {

                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {

                    return "";
                }
            else
            {
                if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == EMPTY)//movement
                {
                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow() + 1, a->getCol(), BOGEY);
                    a->setRow(a->getRow() + 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == PLAYER)//attack
                {
                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {
                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return"";
                }
            }
        }
        else //both row and col are diff so randomly choose whether to move cols or rows
        {
            int i = 0;
            int x = randInt(1, 2);
            while (i < 2)
            {
                switch (x)
                {
                case 1:
                    if (colDir)
                    {
                        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == EMPTY)//movement
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow(), a->getCol() - 1, BOGEY);
                            a->setCol(a->getCol() - 1);
                            i += 2;
                        }
                        else
                        {
                            x = 2;
                            i++;
                        }
                    }
                    else
                    {
                        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == EMPTY)//movement
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow(), a->getCol() + 1, BOGEY);
                            a->setCol(a->getCol() + 1);
                            i += 2;
                        }
                        else
                        {
                            x = 2;
                            i++;
                        }
                    }
                    break;
                case 2:
                    if (rowDir)
                    {

                        if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == EMPTY)//movement
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow() - 1, a->getCol(), BOGEY);
                            a->setRow(a->getRow() - 1);
                            i += 2;
                        }
                        else
                        {
                            x = 1;
                            i++;
                        }
                    }
                    else
                    {
                        if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == EMPTY)//movement
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow() + 1, a->getCol(), BOGEY);
                            a->setRow(a->getRow() + 1);
                            i += 2;
                        }
                        else
                        {
                            x = 1;
                            i++;
                        }
                    }
                    break;
                }

            }
            return"";
        }
    }

}

string Game::SnakeMove(Actor* a)
{
    //same as Bogey except only range of 3 and can make player sleep
    if (a->getSleep() != 0)
    {
        a->setSleep(-1);
        return "";
    }
    string attack = "";
    bool rowDir = abs(a->getRow() + 1 - player->getRow()) > abs(a->getRow() - 1 - player->getRow());
    bool colDir = abs(a->getCol() + 1 - player->getCol()) > abs(a->getCol() - 1 - player->getCol());
    if (abs(a->getRow() - player->getRow()) + abs(a->getCol() - player->getCol()) > 3)
    {
        return"";
    }
    else
    {
        if (a->getRow() == player->getRow())
        {
            if (colDir)
                if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == EMPTY)
                {

                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow(), a->getCol() - 1, SNAKE);
                    a->setCol(a->getCol() - 1);
                    return "";
                }
                else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == PLAYER)
                {
                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {
                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (trueWithProbability(1.0 / 5))
                        {
                            player->setSleep(randInt(2, 6));
                            attack = "and hits, putting " + player->name() + "to sleep.\n";
                        }
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return "";
                }
            else
            {
                if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == EMPTY)
                {

                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow(), a->getCol() + 1, SNAKE);
                    a->setCol(a->getCol() + 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == PLAYER)
                {

                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {

                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (trueWithProbability(1.0 / 5))
                        {
                            player->setSleep(randInt(2, 6));
                            attack = "and hits, putting " + player->name() + "to sleep.\n";
                        }
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return"";
                }
            }
        }
        else if (a->getCol() == player->getCol())
        {
            if (rowDir)
                if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == EMPTY)
                {
                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow() - 1, a->getCol(), SNAKE);
                    a->setRow(a->getRow() - 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == PLAYER)
                {

                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {

                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (trueWithProbability(1.0 / 5))
                        {
                            player->setSleep(randInt(2, 6));
                            attack = "and hits, putting " + player->name() + "to sleep.\n";
                        }
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {

                    return "";
                }
            else
            {
                if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == EMPTY)
                {
                    m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                    m_dungeon->setCellStatus(a->getRow() + 1, a->getCol(), SNAKE);
                    a->setRow(a->getRow() + 1);
                    return"";
                }
                else if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == PLAYER)
                {
                    if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                        attack = "and misses.\n";
                    else
                    {
                        attack = "and hits.\n";
                        player->changehp(-a->damPoints());
                        if (trueWithProbability(1.0 / 5))
                        {
                            player->setSleep(randInt(2, 6));
                            attack = "and hits, putting " + player->name() + "to sleep.\n";
                        }
                        if (player->gethp() <= 0)
                        {
                            attack = "dealing a final blow.\n";
                            player->setDead();
                        }
                    }
                    return a->attack(PLAYER) + attack;
                }
                else
                {
                    return"";
                }
            }
        }
        else
        {
            int i = 0;
            int x = randInt(1, 2);
            while (i < 2)
            {
                switch (x)
                {
                case 1:
                    if (colDir)
                    {
                        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == EMPTY)
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow(), a->getCol() - 1, SNAKE);
                            a->setCol(a->getCol() - 1);
                            i += 2;
                        }
                        else
                        {
                            x = 2;
                            i++;
                        }
                    }
                    else
                    {
                        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == EMPTY)
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow(), a->getCol() + 1, SNAKE);
                            a->setCol(a->getCol() + 1);
                            i += 2;
                        }
                        else
                        {
                            x = 2;
                            i++;
                        }
                    }
                    break;
                case 2:
                    if (rowDir)
                    {

                        if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == EMPTY)
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow() - 1, a->getCol(), SNAKE);
                            a->setRow(a->getRow() - 1);
                            i += 2;
                        }
                        else
                        {
                            x = 1;
                            i++;
                        }
                    }
                    else
                    {
                        if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == EMPTY)
                        {
                            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
                            m_dungeon->setCellStatus(a->getRow() + 1, a->getCol(), SNAKE);
                            a->setRow(a->getRow() + 1);
                            i += 2;
                        }
                        else
                        {
                            x = 1;
                            i++;
                        }
                    }
                    break;
                }

            }
            return"";
        }
    }
}

string Game::DragonMove(Actor* a)
{
    if (trueWithProbability(1.0 / 10))//regain health
        a->changehp(1);
    if (a->getSleep() != 0)
    {
        a->setSleep(-1);
        return "";
    }
    string attack = "";
    //only does anything and attacks when player is next to it
    if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == PLAYER)
    {
        if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
            attack = "and misses.\n";
        else
        {
            attack = "and hits.\n";
            player->changehp(-a->damPoints());
            if (player->gethp() <= 0)
            {
                attack = "dealing a final blow.\n";
                player->setDead();
            }
        }
        return a->attack(PLAYER) + attack;
    }
    else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == PLAYER)
    {

        if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
            attack = "and misses.\n";
        else
        {

            attack = "and hits.\n";
            player->changehp(-a->damPoints());
            if (player->gethp() <= 0)
            {
                attack = "dealing a final blow.\n";
                player->setDead();
            }
        }
        return a->attack(PLAYER) + attack;
    }
    else if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == PLAYER)
    {

        if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
            attack = "and misses.\n";
        else
        {
            attack = "and hits.\n";
            player->changehp(-a->damPoints());
            if (player->gethp() <= 0)
            {
                attack = "dealing a final blow.\n";
                player->setDead();
            }
        }
        return a->attack(PLAYER) + attack;
    }
    else if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == PLAYER)
    {
        if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
            attack = "and misses.\n";
        else
        {
            attack = "and hits.\n";
            player->changehp(-a->damPoints());
            if (player->gethp() <= 0)
            {
                attack = "dealing a final blow.\n";
                player->setDead();
            }
        }
        return a->attack(PLAYER) + attack;
    }
    else
    {
        return"";
    }
}


string Game::GoblinMove(Actor* a, int n)
{
    if (a->getSleep() != 0)
    {
        a->setSleep(-1);
        return "";
    }
    while (!goblinCoords.empty()) // empty the queue
        goblinCoords.pop();
    string attack = "";
    Coord b(player->getRow(), player->getCol());
    goblinCoords.push(b); //take in the player position
    string holder = pathExists(a, b, b, n); //find direction to travel
    if (holder == "")
        return "";

    if (holder == "up")
    {
        if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
            m_dungeon->setCellStatus(a->getRow() - 1, a->getCol(), GOBLIN);
            a->setRow(a->getRow() - 1);
            return"";
        }
        else if (m_dungeon->getCellStatus(a->getRow() - 1, a->getCol()) == PLAYER)//attack
        {
            if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                attack = "and misses.\n";
            else
            {

                attack = "and hits.\n";
                player->changehp(-a->damPoints());
                if (player->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    player->setDead();
                }
            }
            return a->attack(PLAYER) + attack;
        }
    }
    else if (holder == "right")
    {
        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
            m_dungeon->setCellStatus(a->getRow(), a->getCol() + 1, GOBLIN);
            a->setCol(a->getCol() + 1);
            return"";
        }
        else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() + 1) == PLAYER)//attack
        {
            if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                attack = "and misses.\n";
            else
            {

                attack = "and hits.\n";
                player->changehp(-a->damPoints());
                if (player->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    player->setDead();
                }
            }
            return a->attack(PLAYER) + attack;
        }
    }
    else if (holder == "down")
    {
        if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
            m_dungeon->setCellStatus(a->getRow() + 1, a->getCol(), GOBLIN);
            a->setRow(a->getRow() + 1);
            return"";
        }
        else if (m_dungeon->getCellStatus(a->getRow() + 1, a->getCol()) == PLAYER)//attack
        {
            if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                attack = "and misses.\n";
            else
            {

                attack = "and hits.\n";
                player->changehp(-a->damPoints());
                if (player->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    player->setDead();
                }
            }
            return a->attack(PLAYER) + attack;
        }
    }
    else if (holder == "left")
    {
        if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == EMPTY)//movement
        {
            m_dungeon->setCellStatus(a->getRow(), a->getCol(), EMPTY);
            m_dungeon->setCellStatus(a->getRow(), a->getCol() - 1, GOBLIN);
            a->setCol(a->getCol() - 1);
            return"";
        }
        else if (m_dungeon->getCellStatus(a->getRow(), a->getCol() - 1) == PLAYER)//attack
        {
            if (randInt(1, player->defPoints()) <= randInt(1, a->attPoints()))
                attack = "and misses.\n";
            else
            {
                attack = "and hits.\n";
                player->changehp(-a->damPoints());
                if (player->gethp() <= 0)
                {
                    attack = "dealing a final blow.\n";
                    player->setDead();
                }
            }
            return a->attack(PLAYER) + attack;
        }
    }
    return "";
}



// You will presumably add to this project other .h/.cpp files for the
// various classes of objects you need to play the game:  player, monsters,
// weapons, etc.  You might have a separate .h/.cpp pair for each class
// (e.g., Player.h, Boegeyman.h, etc.), or you might put the class
// declarations for all actors in Actor.h, all game objects in GameObject.h,
// etc.
