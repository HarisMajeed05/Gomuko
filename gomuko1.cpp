#include<conio.h>
#include<iostream>
#include<math.h>
#include<iomanip>

using namespace std;

void init(char B[][19], int dim, string pnames[],
    //int nop,
    char sym[], int& tu)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            B[r][c] = '-';
        }
    }
    for (int r = 1; r < 2; r++)
    {
        cout << "Player " << r << " name :";
        string a;
        cin >> a;
        pnames[r] = a;
        cout << "Player " << r << " symbol :";
        char b;
        cin >> b;
        sym[r] = b;
    }
    tu = rand() % 2;//nop

}
void printboard(char B[][19], int dim)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            cout << setw(2) << B[r][c];
        }cout << endl;
    }
}
void turnmsg(string a)
{
    cout << a << "'s turn  \n";
}
void placemove(char B[][19], int pr, int pc, char sym)
{
    B[pr][pc] = sym;
}
void turnch(int& tu
    // , int nop
)
{
    tu = (tu + 1) % 2; //nop;
}
bool isvalid(char B[][19], int dim, int r, int c)
{
    return (r >= 0 && r < dim) && (c >= 0 && c < dim) && (B[r][c] == '-');
}
bool hori(char B[][19], int dim, int r, int c, char sym, int wincount)
{
    if (c + wincount > dim)
        return false;
    int count = 0;
    for (int i = 0; i < wincount; i++)
        if (B[r][c + i] == sym)
            count++;
    if (count == wincount)
        return true;
    return false;

}
bool ver(char B[][19], int dim, int r, int c, char sym, int wincount)
{
    if (r + wincount > dim)
        return false;
    int count = 0;
    for (int i = 0; i < wincount; i++)
        if (B[r + i][c] == sym)
            count++;
    if (count == wincount)
        return true;
    return false;

}
bool digLR(char B[][19], int dim, int r, int c, char sym, int wincount)
{
    int count = 0;
    for (int i = 0; i < wincount; i++)
        if (B[r + i][c + i] == sym)
            count++;
    if (count == wincount)
        return true;
    return false;

}
bool digRL(char B[][19], int dim, int r, int c, char sym, int wincount)
{
    int count = 0;
    for (int i = 0; i < wincount; i++)
        if (B[r + i][c - i] == sym)
            count++;
    if (count == wincount)
        return true;
    return false;

}
bool win(char B[][19], int dim, char smb[], int wincount, int t)
{
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (hori(B, dim, r, c, smb[t], wincount))
                return true;
            if (ver(B, dim, r, c, smb[t], wincount))
                return true;
            if (digLR(B, dim, r, c, smb[t], wincount))
                return true;
            if (digRL(B, dim, r, c, smb[t], wincount))
                return true;
        }
    }
    return false;
}
bool draw(char B[][19], int dim)
{
    int count = 0;
    for (int r = 0; r < dim; r++)
    {
        for (int c = 0; c < dim; c++)
        {
            if (B[r][c] == '-')
                count++;
        }
    }
    if (count == 0)
        return true;
    else
        return false;
}
void computer(char B[][19], int dim, int& R, int& C, char sym[], int wincount, int turn
    //, int nop
)
{
    for (int w = wincount; w > 1; w--)
    {
        for (int r = 0; r < dim; r++)
        {
            for (int c = 0; c < dim; c++)
            {
                if (isvalid(B, dim, r, c))
                {
                    B[r][c] = sym[turn];
                    if (win(B, dim, sym, w, turn))
                    {
                        B[r][c] = '-';
                        R = r; C = c;
                    }
                    B[r][c] = '-';
                }
            }
        }int t2 = 0;
        if (turn < 2)//nop)
        {
            t2++;
            for (int r = 0; r < dim; r++)
            {
                for (int c = 0; c < dim; c++)
                {
                    if (isvalid(B, dim, r, c))
                    {
                        B[r][c] = sym[t2];
                        if (win(B, dim, sym, w, t2))
                        {
                            B[r][c] = '-';
                            R = r; C = c;
                            return;
                        }
                        B[r][c] = '-';
                    }
                }
            }
        }
    }
}


int main()
{
    char B[19][19];
    int dim,
        // nop, 
        turn = 0, row = 0, col = 0, wincount = 0, gm = 0;
    cout << "Enter Dimension! ";
    cin >> dim;
    if (dim == 3)
    {
        wincount = 3;
    }
    else
    {
        cout << "Enter win count: ";
        cin >> wincount;
    }
    // cout << "Enter Number of Players: ";
    // cin >> nop;

    const int l = 5;
    string pnames[l];
    pnames[0] = "Computer";
    char sym[l];
    sym[0] = '*';
    init(B, dim, pnames,
        // nop,
        sym, turn);
    while (gm == 0)
    {
        system("Cls");
        printboard(B, dim); cout << "\n";
        turnmsg(pnames[turn]);
        if (turn == 0)
        {
            computer(B, dim, row, col, sym, wincount, turn);//, nop);
        }
        else {
            do
            {
                cout << "enter row: ";
                cin >> row;
                cout << "\nenter col: ";
                cin >> col;
                row = row - 1;
                col = col - 1;
            } while (!isvalid(B, dim, row, col));
        }
        placemove(B, row, col, sym[turn]);
        if (win(B, dim, sym, wincount, turn))
        {
            system("Cls");
            printboard(B, dim);
            cout << "\n\nPlayer " << turn + 1 << " " << pnames[turn] << " WINS!\n\n";
            gm = 1;
        }
        if (draw(B, dim))
        {
            system("Cls");
            printboard(B, dim);
            cout << "\n\nGame Draw \n\n";
            gm = 1;
        }
        turnch(turn);//, nop);

    }
}