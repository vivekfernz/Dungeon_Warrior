#ifndef Actor_h
#define Actor_h
#include <string>
class GameObject;
class Inventory;

class Actor
{
public:
	Actor(int row, int col);
	virtual ~Actor();

	//Getters
	int getRow();
	int getCol();
	int getSleep();
	virtual int gethp() = 0;
	virtual int getap() = 0;
	virtual int getdp() = 0;
	virtual int getsp() = 0;
	virtual bool isDead() = 0;
	virtual int defPoints() = 0;
	virtual int attPoints() = 0;
	virtual int damPoints() = 0;
	virtual int getCellStatus(int r, int c) = 0;
	virtual GameObject* getWeapon() = 0;
	virtual std::string name() = 0;
	virtual std::string attack(int target) = 0;

	//Setters
	void setRow(int n);
	void setCol(int n);
	void setSleep(int n);
	virtual void setDead() = 0;
	virtual void setCellStatus(int r, int c, int s) = 0;

	//Mutator
	virtual void changehp(int n) = 0;

private:
	int m_row;
	int m_col;
	int m_sleep;
};

class Player :public Actor
{
public:
	Player(int row, int col);
	~Player();

	//Setter
	void setmaxhp(int n);
	void setsp(int n); //for cheating, did cheat for hp in mutator

	//Getter
	int getmaxhp();
	int gethp();
	int getap();
	int getdp();
	int getsp();
	GameObject* getWeapon();
	bool isDead();
	bool hasTrophy();


	//Mutator
	void changehp(int n);
	void increasemaxhp();
	void increaseap();
	void increasedp();
	void increasesp();
	int defPoints();
	int attPoints();
	int damPoints();
	int getCellStatus(int r, int c);
	std::string attack(int target);
	std::string name();

	//Setters
	void setWeapon(GameObject* weap);
	void setDead();
	void setTrophy(bool result);
	void setCellStatus(int r, int c, int status);

private:
	int m_hp;
	int m_ap;
	int m_sp;
	int m_dp;
	int maxhp;
	bool m_dead;
	bool m_trophy;
	GameObject* m_weapon;
	std::string m_name;
};

//Goblin
class Goblin :public Actor
{
public:
	Goblin(int row, int col);
	~Goblin();

	//getter
	int gethp();
	int getap();
	int getdp();
	int getsp();
	bool isDead();
	std::string attack(int target);
	GameObject* getWeapon();
	int defPoints();
	int attPoints();
	int damPoints();
	std::string name();
	int getCellStatus(int r, int c);

	//Mutator
	void changehp(int n);

	//Setter
	void setDead();
	void setCellStatus(int r, int c, int status);


private:
	int m_hp;
	int m_ap;
	int m_sp;
	int m_dp;
	bool m_dead;
	std::string m_name;
	GameObject* m_weapon;
	int m_grid[18][70];
};

//Dragon
class Dragon :public Actor
{
public:
	Dragon(int row, int col);
	~Dragon();



	//getter
	int getmaxhp();
	int gethp();
	int getap();
	int getdp();
	int getsp();
	bool isDead();
	std::string attack(int target);
	GameObject* getWeapon();
	int defPoints();
	int attPoints();
	int damPoints();
	std::string name();
	int getCellStatus(int r, int c);

	//Mutator
	void changehp(int n);

	//Setter
	void setDead();
	void setCellStatus(int r, int c, int status);

private:
	int maxhp;
	int m_hp;
	int m_ap;
	int m_sp;
	int m_dp;
	bool m_dead;
	GameObject* m_weapon;
	std::string m_name;
};

//SnakeWoman
class SnakeWoman :public Actor
{
public:
	SnakeWoman(int row, int col);
	~SnakeWoman();
	//getter
	int gethp();
	int getap();
	int getdp();
	int getsp();
	bool isDead();
	std::string attack(int target);
	GameObject* getWeapon();
	int defPoints();
	int attPoints();
	int damPoints();
	std::string name();
	int getCellStatus(int r, int c);

	//Mutator
	void changehp(int n);

	//Setter
	void setDead();
	void setCellStatus(int r, int c, int status);

private:
	int m_hp;
	int m_ap;
	int m_sp;
	int m_dp;
	bool m_dead;
	GameObject* m_weapon;
	std::string m_name;
};

//Bogey
class Bogey :public Actor
{
public:
	Bogey(int row, int col);
	~Bogey();
	//getter


//getter
	int gethp();
	int getap();
	int getdp();
	int getsp();
	bool isDead();
	std::string attack(int target);
	GameObject* getWeapon();
	int defPoints();
	int attPoints();
	int damPoints();
	std::string name();
	int getCellStatus(int r, int c);

	//Mutator
	void changehp(int n);

	//Setter
	void setDead();
	void setCellStatus(int r, int c, int status);

private:
	int m_hp;
	int m_ap;
	int m_sp;
	int m_dp;
	bool m_dead;
	GameObject* m_weapon;
	std::string m_name;
};
#endif
