#include <iostream>
using namespace std;

int rows = 9;

void writeArray(int *ar);
// void initializeArray(int *ar, int length);
bool solve(int *feld, int index);
bool isValid(int *feld);

int main()
{
    int feld[rows * rows] = {
        2, 0, 0,   5, 0, 7,   4, 0, 6,
        0, 0, 0,   0, 3, 1,   0, 0, 0,
        0, 0, 0,   0, 0, 0,   2, 3, 0,

        0, 0, 0,   0, 2, 0,   0, 0, 0,
        8, 6, 0,   3, 1, 0,   0, 0, 0,
        0, 4, 5,   0, 0, 0,   0, 0, 0,

        0, 0, 9,   0, 0, 0,   7, 0, 0,
        0, 0, 6,   9, 5, 0,   0, 0, 2,
        0, 0, 1,   0, 0, 6,   0, 0, 8
    };
    // initializeArray(feld, rows * rows);
    writeArray(feld);
    solve(feld, 0);
    writeArray(feld);
}

void writeArray(int *ar)
{
    for (int i = 0; i < rows * rows; i++)
    {
        cout << ar[i] << ((i + 1) % 3 == 0 ? "   " : " ");
        if ((i + 1) % rows == 0){
            cout << endl;
            // formatting
            if((i + 1) / rows % 3 == 0){
                cout << endl;
            }
        }
        
    }
    cout << endl << endl;
}

/*void initializeArray(int *ar, int length)
{
    for (int i = 0; i < length; i++)
    {
        ar[i] = 0;
    }
}*/

bool solve(int *feld, int index)
{
    if (!isValid(feld))
    {
        return false;
    }
    if (index == rows * rows)
    {
        return true;
    }
    if (feld[index] != 0)
    {
        return solve(feld, index + 1);
    }
    for (int i = 1; i <= rows; i++)
    {
        feld[index] = i;
        if (solve(feld, index + 1)){
            return true;
        }
        feld[index] = 0;
    }

    return false;
}

bool isValid(int *feld)
{
    int row;
    int column;
    for (int index = 0; index < rows * rows; index++)
    {
        if(feld[index] == 0){
            continue;
        }
        row = index / rows;
        column = index % rows;

        // horizontal check
        for (int x = row * rows; x < (row + 1) * rows; x++)
        {
            if (x != index && feld[x] == feld[index])
            {
                return false;
            }
        }
        // vertical check
        for (int y = column; y < rows * (rows - 1) + column; y += rows)
        {
            if (y != index && feld[y] == feld[index])
            {
                return false;
            }
        }
        int squareMiddle = index;
        // square check
        // get middle of the square
        if (row % 3 == 0)
        {
            squareMiddle += rows;
        }
        else if (row % 3 == 2)
        {
            squareMiddle -= rows;
        }
        if (column % 3 == 0)
        {
            squareMiddle++;
        }
        else if (column % 3 == 2)
        {
            squareMiddle--;
        }
        // check neighbour squares
        int squares[9] = {
            -rows - 1, -rows, -rows + 1,
            -1, 0, 1,
            rows - 1, rows, rows + 1};
        for (int i = 0; i < 9; i++)
        {
            if (squareMiddle + squares[i] != index && feld[squareMiddle + squares[i]] == feld[index])
            {
                return false;
            }
        }
    }
    return true;
}