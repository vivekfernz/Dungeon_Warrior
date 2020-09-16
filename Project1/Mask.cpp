#include "Mask.h"
#include "globals.h"
using namespace std;

Mask::Mask()
{
	m_row = 18;
	m_col = 70;
	for (int r = 1; r <= m_row; r++)
	{
		for (int c = 1; c <= m_col; c++)
		{
			m_grid[r - 1][c - 1] = WALL;//constructed so everything starts as wall
		}
	}
}

int Mask::getCellStatus(int r, int c)
{
	return m_grid[r - 1][c - 1];
}

void Mask::setCellStatus(int r, int c, int status)
{
	m_grid[r - 1][c - 1] = status;
}