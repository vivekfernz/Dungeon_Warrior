#ifndef GameObject_h
#define GameObject_h
#include <string>
class GameObject
{
public:
	//For Gameobjects already possessed
	GameObject();
	virtual ~GameObject();
	//For gameobjects on the ground
	GameObject(int row, int col);

	//Getter
	int getRow();
	int getCol();
	virtual std::string name() = 0;
	virtual bool isWeapon() = 0;
	virtual std::string action() = 0;
	virtual int getdext() = 0;
	virtual int getdam() = 0;
private:
	int m_row;
	int m_col;
};

class Trophy : public GameObject
{
public:
	Trophy(int row, int col);
	std::string name();
	bool isWeapon();
	std::string action();
	int getdext();
	int getdam();
private:
	std::string m_name;
};

class Stair
{
public:
	Stair(int row, int col);

	//Getter
	int getRow();
	int getCol();

private:
	int m_row;
	int m_col;
};
#endif // !GameObject_h

