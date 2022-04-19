#include <iostream>
#include <string>
#include <windows.h>
using namespace std;
bool checknull(int x, int  y, int PlayerTurn);

class Piece {
protected:
	int Player;
	string Name;
public:
	Piece()
	{
		Player = 0;
		Name = " ";
	}
	Piece(string piece, int player)
	{
		Player = player;
		Name = piece;
	}
	string PieceName()
	{
		return Name;
	}
	int PlayerName()
	{
		return Player;
	}
	virtual bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		return true;
	}
	//friend bool BlockCheck(int x, int  y, int PlayerTurn);
	friend bool PlayerPieceCheck(int x, int  y, int PlayerTurn);
};
class Pawns :public Piece {
	int inatial;
public:
	Pawns(string name, int player) :Piece(name, player)
	{
		inatial = 0;
	}
	friend void PP(int Xi, int Yi, int Xf, int Yf, int PlayerTurn);

	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)//move wala hoga
	{
		if (PlayerTurn == 1)
		{
			if (PlayerPieceCheck(Xi + 1, Yf, 2))//// here problem h 2 ku lagaya hwa ha
			{
				if (Xi + 1 == Xf && Yi + 1 == Yf)//right diagonal
				{
					if (Xf == 7) /// ye islia ha agr hmara pawn udr pnch jae mtlb opponent side pr to
					{
						PP(Xi, Yi, Xf, Yf, 1);
					}
					inatial = 1;
					return true;
				}
				else if (Xi + 1 == Xf && Yi - 1 == Yf)//left diagonal
				{
					if (Xf == 7)
					{
						PP(Xi, Yi, Xf, Yf, 1);
					}
					inatial = 1;
					return true;
				}
				else
					return false;
			}
			if (checknull(Xi + 1, Yi, PlayerTurn) && !PlayerPieceCheck(Xi + 1, Yi, 1) && !PlayerPieceCheck(Xi + 1, Yi, 2))
			{
				if (Xi + 1 == Xf && Yi == Yf)///1 down
				{
					if (Xf == 7)
					{
						PP(Xi, Yi, Xf, Yf, 1);
					}
					inatial = 1;
					return true;
				}
				else if (checknull(Xi + 2, Yi, PlayerTurn) && !PlayerPieceCheck(Xi + 1, Yi, 1) && !PlayerPieceCheck(Xi + 1, Yi, 2) && Xi + 2 == Xf && Yi == Yf && !inatial)
				{
					if (Xf == 7)
					{
						PP(Xi, Yi, Xf, Yf, 1);
					}
					inatial = 1;
					return true;
				}
				else
				{
					return false;
				}

			}
			else
				return false;
		}
		else
		{
			if (PlayerPieceCheck(Xi - 1, Yf, 1))
			{
				if (Xi - 1 == Xf && Yi + 1 == Yf)///right diagonal
				{
					if (Xf == 0)
					{
						PP(Xi, Yi, Xf, Yf, 2);
					}
					inatial = 1;
					return true;
				}
				else if (Xi - 1 == Xf && Yi - 1 == Yf)/////left upper diagonal
				{
					if (Xf == 0)
					{
						PP(Xi, Yi, Xf, Yf, 2);
					}
					inatial = 1;
					return true;
				}
				else
					return false;
			}
			if (checknull(Xi - 1, Yi, PlayerTurn) && !PlayerPieceCheck(Xi - 1, Yi, 1) && !PlayerPieceCheck(Xi - 1, Yi, 2))
			{
				if (Xi - 1 == Xf && Yi == Yf)/// 1 up
				{
					if (Xf == 0)
					{
						PP(Xi, Yi, Xf, Yf, 2);
					}
					inatial = 1;
					return true;
				}
				else if (checknull(Xi - 2, Yi, PlayerTurn) && !PlayerPieceCheck(Xi - 2, Yi, 1) && !PlayerPieceCheck(Xi - 2, Yi, 2) && Xi - 2 == Xf && Yi == Yf && !inatial)
				{
					if (Xf == 0)
					{
						PP(Xi, Yi, Xf, Yf, 2);
					}
					inatial = 1;
					return true;
				}
				else
				{
					return false;
				}
			}
			else
				return false;
		}
	}
};
class Rooks :public Piece {
public:
	Rooks(string name, int player) :Piece(name, player)
	{

	}
	bool MovementRooks(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (Xi == Xf)
		{
			for (int i = Yi + 1; i < Yf; i++)
			{
				if (!checknull(Xf, i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else if (Yi == Yf)
		{
			for (int i = Xi + 1; i < Xf; i++)
			{
				if (!checknull(i, Yf, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (PlayerTurn == 1)
		{
			if (PlayerPieceCheck(Xf, Yf, 2) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementRooks(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
		else
		{
			if (PlayerPieceCheck(Xf, Yf, 1) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementRooks(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
	}
};
class Knights :public Piece {
public:
	Knights(string name, int player) :Piece(name, player)
	{

	}
	bool KnightCheck(int Xi, int Yi, int Xf, int Yf, int PlayerTurn, int checkOn)
	{
		if ((Xi + 2 == Xf && Yi + 1 == Yf) && (PlayerPieceCheck(Xi + 2, Yi + 1, checkOn) || checknull(Xi + 2, Yi + 1, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi + 2 == Xf && Yi - 1 == Yf) && (PlayerPieceCheck(Xi + 2, Yi - 1, checkOn) || checknull(Xi + 2, Yi - 1, PlayerTurn)))
		{
			{
				return true;
			}
		}
		if ((Xi - 2 == Xf && Yi + 1 == Yf) && (PlayerPieceCheck(Xi - 2, Yi + 1, checkOn) || checknull(Xi - 2, Yi + 1, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi - 2 == Xf && Yi - 1 == Yf) && (PlayerPieceCheck(Xi - 2, Yi - 1, checkOn) || checknull(Xi - 2, Yi - 1, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi + 1 == Xf && Yi + 2 == Yf) && (PlayerPieceCheck(Xi + 1, Yi + 2, checkOn) || checknull(Xi + 1, Yi + 2, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi + 1 == Xf && Yi - 2 == Yf) && (PlayerPieceCheck(Xi + 1, Yi - 2, checkOn) || checknull(Xi + 1, Yi - 2, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi - 1 == Xf && Yi + 2 == Yf) && (PlayerPieceCheck(Xi - 1, Yi + 2, checkOn) || checknull(Xi - 1, Yi + 2, PlayerTurn)))
		{

			{
				return true;
			}
		}
		if ((Xi - 1 == Xf && Yi - 2 == Yf) && (PlayerPieceCheck(Xi - 1, Yi - 2, checkOn) || checknull(Xi - 1, Yi - 2, PlayerTurn)))
		{
			{
				return true;
			}
		}
		else
			return false;
	}
	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (PlayerTurn == 1)
		{
			return KnightCheck(Xi, Yi, Xf, Yf, PlayerTurn, 2);
		}
		else
		{
			return KnightCheck(Xi, Yi, Xf, Yf, PlayerTurn, 1);
		}
	}
};
class Bishops :public Piece {
public:
	Bishops(string name, int player) :Piece(name, player)
	{

	}
	bool MovementBishops(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (Xf > Xi && Yf < Yi && Xf - Xi == Yi - Yf)
		{
			for (int i = 1; i + Xi < Xf - 1; i++)
			{
				if (!checknull(Xi + i, Yi - i, PlayerTurn))
				{
					return false;
				}

			}
			return true;
		}
		else if (Xf < Xi && Yf < Yi &&  Xi - Xf == Yi - Yf)
		{
			for (int i = 1; Xi - i < Xf + 1; i++)
			{
				if (!checknull(Xi - i, Yi - i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else if (Xf > Xi && Yf > Yi && Xf - Xi == Yf - Yi)
		{
			for (int i = 1; i + Xi < Xf - 1; i++)
			{
				if (!checknull(Xi + i, Yi + i, PlayerTurn))
				{
					return false;
				}

			}
			return true;
		}
		else if (Xf < Xi && Yf > Yi &&  Xi - Xf == Yf - Yi)
		{
			for (int i = 1; Xi - i < Xf + 1; i++)
			{
				if (!checknull(Xi - i, Yi + i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}
	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (PlayerTurn == 1)
		{
			if (PlayerPieceCheck(Xf, Yf, 2) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementBishops(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
		else
		{
			if (PlayerPieceCheck(Xf, Yf, 1) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementBishops(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
	}
};
class Queen :public Piece {
public:
	Queen(string name, int player) :Piece(name, player)
	{

	}
	bool MovementQueen(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (Xi == Xf)
		{
			for (int i = Yi + 1; i < Yf; i++)
			{
				if (!checknull(Xf, i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else if (Yi == Yf)
		{
			for (int i = Xi + 1; i < Xf; i++)
			{
				if (!checknull(i, Yf, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else if (Xf > Xi && Yf < Yi && Xf - Xi == Yi - Yf)
		{
			for (int i = 1; i + Xi < Xf - 1; i++)
			{
				if (!checknull(Xi + i, Yi - i, PlayerTurn))
				{
					return false;
				}

			}
			return true;
		}
		else if (Xf < Xi && Yf < Yi &&  Xi - Xf == Yi - Yf)
		{
			for (int i = 1; Xi - i < Xf + 1; i++)
			{
				if (!checknull(Xi - i, Yi - i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else if (Xf > Xi && Yf > Yi && Xf - Xi == Yf - Yi)
		{
			for (int i = 1; i + Xi < Xf - 1; i++)
			{
				if (!checknull(Xi + i, Yi + i, PlayerTurn))
				{
					return false;
				}

			}
			return true;
		}
		else if (Xf < Xi && Yf > Yi &&  Xi - Xf == Yf - Yi)
		{
			for (int i = 1; Xi - i < Xf + 1; i++)
			{
				if (!checknull(Xi - i, Yi + i, PlayerTurn))
				{
					return false;
				}
			}
			return true;
		}
		else
			return false;
	}
	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (PlayerTurn == 1)
		{
			if (PlayerPieceCheck(Xf, Yf, 2) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementQueen(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
		else
		{
			if (PlayerPieceCheck(Xf, Yf, 1) || checknull(Xf, Yf, PlayerTurn))
			{
				return MovementQueen(Xi, Yi, Xf, Yf, PlayerTurn);
			}
		}
	}

};
class King :public Piece {
public:
	King(string name, int player) :Piece(name, player)
	{

	}
	bool MovementKing(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (Xi + 1 == Xf && Yi == Yf)
		{
			return true;
		}
		else if (Xi - 1 == Xf && Yi == Yf)
		{
			return true;
		}
		else if (Xi == Xf && Yi + 1 == Yf)
		{
			return true;
		}
		else if (Xi == Xf && Yi - 1 == Yf)
		{
			return true;
		}

		else if (Xi + 1 == Xf && Yi + 1 == Yf)
		{
			return true;
		}
		else if (Xi + 1 == Xf && Yi - 1 == Yf)
		{
			return true;
		}
		else if (Xi - 1 == Xf && Yi + 1 == Yf)
		{
			return true;
		}
		else if (Xi - 1 == Xf && Yi - 1 == Yf)
		{
			return true;
		}
		else
			return false;
	}
	bool Move(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
	{
		if (PlayerTurn == 1)
		{
			if ((PlayerPieceCheck(Xf, Yf, 2) || checknull(Xf, Yf, PlayerTurn)))
			{
				return  MovementKing(Xi, Yi, Xf, Yf, PlayerTurn);
			}
			else
			{
				return false;
			}

		}
		else
		{
			if (PlayerPieceCheck(Xf, Yf, 1) || checknull(Xf, Yf, PlayerTurn))
			{
				return  MovementKing(Xi, Yi, Xf, Yf, PlayerTurn);
			}
			else
			{
				return false;
			}
		}
	}
};
Piece *Board[8][8];
int PlayerTurn = 1;
int winner = 0;
void Inatilize();
void Display();
void Movement(int row, int column, int row2, int column2);
bool PlayerPieceCheck(int x, int  y, int Player);
bool CheckNull(int x, int  y, int PlayerTurn);
int main(void)
{
	int rowi;
	char coli;
	int column;
	int row_d;
	int column_2;
	
	char colum_d;
	Inatilize();


	while (winner == 0)
	{
		Display();

		cout << "\n\n\tTurn of Player :" << PlayerTurn << endl;
		cout << "Enter the Row of Piece ( 0 - 7 ) :";
		cin >> rowi;
		cout << "Enter the Column of Piece (a - h) :";
		cin >> coli;
		cout << "Enter the Row of Piece where to move ( 0 - 7 ) :";
		cin >> row_d;

		cout << "Enter the Column of Piece where to move (a - h) :";
		cin >> colum_d;
		if (coli >= 'A' && coli <= 'H')
		{
			column = coli - 65;
		}
		else if (coli >= 'a' && coli <= 'h')
		{
			column = coli - 97;
		}

		if (coli >= 'A' && coli <= 'H')
		{
			column_2 = colum_d - 65;
		}
		else if (coli >= 'a' && coli <= 'h')
		{
			column_2 = colum_d - 97;
		}
		if ((rowi >= 0 && rowi <= 7) && (column >= 0 && column <= 7) && (row_d >= 0 && row_d <= 7) && (column_2 >= 0 && column_2 <= 7))
		{
			Movement(rowi, column, row_d, column_2);
		}
		system("cls");
	}
	if (winner == 1)
	{
		cout << "\n\nPlayer 1 Won!\n\n";
	}
	else
	{
		cout << "\n\nPlayer 2 Won!\n\n";
	}

	system("pause");
}
void Inatilize()
{
	Board[0][0] = new Rooks("R", 1);
	Board[0][1] = new Knights("k", 1);
	Board[0][2] = new Bishops("B", 1);
	Board[0][3] = new Queen("Q", 1);
	Board[0][4] = new King("K", 1);
	Board[0][5] = new Bishops("B", 1);
	Board[0][6] = new Knights("k", 1);
	Board[0][7] = new Rooks("R", 1);
	Board[1][0] = new Pawns("P", 1);
	Board[1][1] = new Pawns("P", 1);
	Board[1][2] = new Pawns("P", 1);
	Board[1][3] = new Pawns("P", 1);
	Board[1][4] = new Pawns("P", 1);
	Board[1][5] = new Pawns("P", 1);
	Board[1][6] = new Pawns("P", 1);
	Board[1][7] = new Pawns("P", 1);

	Board[7][0] = new Rooks("R", 2);
	Board[7][1] = new Knights("k", 2);
	Board[7][2] = new Bishops("B", 2);
	Board[7][3] = new Queen("Q", 2);
	Board[7][4] = new King("K", 2);
	Board[7][5] = new Bishops("B", 2);
	Board[7][6] = new Knights("k", 2);
	Board[7][7] = new Rooks("R", 2);
	Board[6][0] = new Pawns("P", 2);
	Board[6][1] = new Pawns("P", 2);
	Board[6][2] = new Pawns("P", 2);
	Board[6][3] = new Pawns("P", 2);
	Board[6][4] = new Pawns("P", 2);
	Board[6][5] = new Pawns("P", 2);
	Board[6][6] = new Pawns("P", 2);
	Board[6][7] = new Pawns("P", 2);
	for (int i = 2; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Board[i][j] = NULL;
		}
	}
	
}
void Display()
{
	cout << "\n\n\t\t\t\tC H E S S\n\n";

	cout << '\t';
	for (int j = 0; j < 8; j++)        /////// out Lines
	{
		cout << "   " << static_cast<char>(j + 97) << "   ";
	}

	cout << endl << endl;
	
	
	for (int i = 0; i < 8; i++)
	{
		cout << '\t';
		for (int j = 0; j < 8; j++)        /////// out Lines
		{
			cout << "_______";
		}
		cout << '_' << endl;

		cout << '\t';
		for (int j = 0; j < 8; j++)    ////Spacing///
		{
			cout << "|      ";
		}
		cout << '|' << endl;

		cout << "    " << i << "   ";
		for (int j = 0; j < 8; j++)          /////// Main Pieces///////
		{
			if (Board[i][j] != NULL)
			{
				cout << "|  " << Board[i][j]->PieceName() << Board[i][j]->PlayerName() << "  ";
			}
			else
			{
				cout << "|      ";
			}
		}
		cout << '|' << "    " << i << endl;

		cout << '\t';
		for (int j = 0; j < 8; j++)    ////Spacing///
		{
			cout << "|      ";
		}
		cout << '|' << endl;
	}

	cout << '\t';
	for (int j = 0; j < 8; j++)        /////// out Lines
	{
		cout << "_______";
	}
	cout << '_' << endl;
}
bool PlayerPieceCheck(int x, int  y, int Player)
{
	if (Board[x][y] == NULL)
	{
		return false;
	}
	else if (Board[x][y]->PlayerName() == Player)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool checknull(int x, int  y, int PlayerTurn)
{
	if (Board[x][y] == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}

}
void Movement(int Xi, int Yi, int Xf, int Yf)
{
	if (Board[Xi][Yi] == NULL)   ///initial position zero to nhi ha
	{
		
	}
	else if (PlayerTurn == Board[Xi][Yi]->PlayerName())    ///idr player num leta ha aur idr name piece k name
	{
		if (Board[Xf][Yf] == NULL || PlayerTurn != Board[Xf][Yf]->PlayerName()) // destiny zero ha kya 
		{
			if (Board[Xi][Yi]->Move(Xi, Yi, Xf, Yf, PlayerTurn)) ///jis piece ne move krna hota move wale ko call krta ha
			{
				if (!checknull(Xf, Yf, PlayerTurn))
				{
					if ((Board[Xf][Yf]->PlayerName() != PlayerTurn) && (Board[Xf][Yf]->PieceName() == "K"))
					{
						if (PlayerTurn == 1)
						{
							winner = 1;
						}
						else
						{
							winner = 2;
						}
					}
				}
				Board[Xf][Yf] = Board[Xi][Yi];
				Board[Xi][Yi] = NULL;
				if (PlayerTurn == 1)
					PlayerTurn = 2;
				else
					PlayerTurn = 1;
			}
		}
	}
}
void PP(int Xi, int Yi, int Xf, int Yf, int PlayerTurn)
{
	system("cls");
	int num;
	cout << "\t\t: Pawn permotion :\n";
	cout << "Enter Your choice in which you want to promote Pawn\n";
	cout << "1 --> Queen\n";
	cout << "2 --> Knight\n";
	cout << "3 --> Rook\n";
	cout << "4 --> Bishop\n";
	cout << "Enter number ::";
	cin >> num;
	switch (num)
	{
	case 1:
		Board[Xi][Yi] = new Queen("Q", PlayerTurn);
		break;
	case 2:
		Board[Xi][Yi] = new Knights("k", PlayerTurn);
		break;
	case 3:
		Board[Xi][Yi] = new Rooks("R", PlayerTurn);
		break;
	case 4:
		Board[Xi][Yi] = new Bishops("B", PlayerTurn);
		break;
	default:
		cout << "Error\n";
	}
}