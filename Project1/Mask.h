#ifndef Mask_h
#define Mask_h
class Mask
{
public:
	Mask();

	//Getter
	int getRow();
	int getCol();
	int getCellStatus(int row, int col);

	//Setter
	void setCellStatus(int row, int col, int status);

private:
	int m_row;
	int m_col;
	int m_grid[18][70];
};
#endif // !Mask_h

