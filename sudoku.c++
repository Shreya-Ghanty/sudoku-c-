    #include <iostream>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <windows.h>
using namespace std;

class Sudoku
  {
    private:
    int board[9][9];
    int change[9][9];
    public:
    Sudoku();
    void Print_Board();  
    void Add_First_Cord();  
    void Solve();
    void Help_Solve(int i, int j);
    bool Check_Conflicts(int p, int i, int j);
  };

Sudoku Game;  

void setcolor(unsigned short color)                 //The function that you'll use to
{                                                   //set the colour
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon,color);
}

Sudoku::Sudoku()
  {
    for(int i = 1; i <= 9; i++)
      for(int j = 1; j <= 9; j++)
        board[i][j] = 0;            
  }

void Sudoku::Print_Board()
  {
    for(int i = 1; i <= 9; i++)
      {
        for(int j = 1; j <= 9; j++)
          {
            if(change[i][j] == 1) 
              {
                setcolor(12);
                cout << board[i][j] << " ";
                setcolor(7);           
              }
              else cout << board[i][j] << " ";  
              if(j%3 == 0) cout << "| ";
          }
        cout << endl;
        if(i%3 == 0) cout << "------+-------+---------" << endl;

      }                    
  }

void Sudoku::Add_First_Cord()
  {
    board[1][1] = 5; change[1][1] = 1;
    board[1][2] = 3; change[1][2] = 1;     
    board[1][5] = 7; change[1][5] = 1;      
    board[2][1] = 6; change[2][1] = 1;  
    board[2][4] = 1; change[2][4] = 1;       
    board[2][5] = 9; change[2][5] = 1;  
    board[2][6] = 5; change[2][6] = 1; 
    board[3][2] = 9; change[3][2] = 1;      
    board[3][3] = 8; change[3][3] = 1;   
    board[3][8] = 6; change[3][8] = 1;     
    board[4][1] = 8; change[4][1] = 1;    
    board[4][5] = 6; change[4][5] = 1;    
    board[4][9] = 3; change[4][9] = 1;    
    board[5][1] = 4; change[5][1] = 1; 
    board[5][4] = 8; change[5][4] = 1;  
    board[5][6] = 3; change[5][6] = 1;  
    board[5][9] = 1; change[5][9] = 1;   
    board[6][1] = 7; change[6][1] = 1; 
    board[6][5] = 2; change[6][5] = 1;   
    board[6][9] = 6; change[6][9] = 1;  
    board[7][2] = 6; change[7][2] = 1;  
    board[7][7] = 2; change[7][7] = 1;  
    board[7][8] = 8; change[7][8] = 1;  
    board[8][4] = 4; change[8][4] = 1; 
    board[8][5] = 1; change[8][5] = 1;   
    board[8][6] = 9; change[8][6] = 1; 
    board[8][9] = 5; change[8][9] = 1;   
    board[9][5] = 8; change[9][5] = 1;  
    board[9][8] = 7; change[9][8] = 1;  
    board[9][9] = 9; change[9][9] = 1;  
  }

bool Sudoku::Check_Conflicts(int p, int i, int j)
  {
    for(int k = 1; k <= 9; k++)
      if(board[i][k] == p) return false;

    for(int q = 1; q <= 9; q++)
      if(board[q][j] == p) return false;

    /*
      *00
      000
      000
    */
    if((j == 1 || j == 4 || j == 7) && (i == 1 || i == 4 || i == 7))
      {
         if(board[i][j+1] == p || board[i][j+2] == p || board[i+1][j] == p || 
             board[i+2][j] == p || board[i+1][j+1] == p || board[i+1][j+2] == p || 
                 board[i+2][j+1] == p || board[i+2][j+2] == p)return false;     
      } 


    /*
      000
      000
      *00
    */  
    if((j == 1 || j == 4 || j == 7) && (i == 3 || i == 6 || i == 9))
      {
         if(board[i-1][j] == p || board[i-2][j] == p || board[i][j+1] == p || 
             board[i][j+2] == p || board[i-1][j+1] == p || board[i-1][j+2] == p || 
                 board[i-2][j+1] == p || board[i-2][j+2] == p)return false;   
      }

    /*
      000
      *00
      000
    */            
    if((j == 1 || j == 4 || j == 7) && (i == 2 || i == 5 || i == 8))
      {
         if(board[i-1][j] == p || board[i+1][j] == p || board[i-1][j+1] == p || 
             board[i][j+1] == p || board[i+1][j+1] == p || board[i+1][j+2] == p || 
                 board[i][j+2] == p || board[i+1][j+2] == p)return false;  
      } 


    /*
      0*0
      000
      000
    */            
    if((j == 2 || j == 5 || j == 8) && (i == 1 || i == 5 || i == 7))
      {
         if(board[i-1][j] == p || board[i+1][j] == p || board[i-1][j+1] == p || 
             board[i][j+1] == p || board[i+1][j+1] == p || board[i+1][j+2] == p || 
                 board[i][j+2] == p || board[i+1][j+2] == p)return false;  
      }

    /*
      000
      0*0
      000
    */            
    if((j == 2 || j == 5 || j == 8) && (i == 2 || i == 5 || i == 8))
      {
         if(board[i-1][j] == p || board[i-1][j-1] == p || board[i-1][j+1] == p || 
             board[i][j+1] == p || board[i][j-1] == p || board[i+1][j+1] == p || 
                 board[i][j] == p || board[i+1][j-1] == p)return false;  
      }


    /*
      000
      000
      0*0
    */            
    if((j == 2 || j == 5 || j == 8) && (i == 3 || i == 6 || i == 9))
      {
         if(board[i][j-1] == p || board[i][j+1] == p || board[i-1][j] == p || 
             board[i-1][j+1] == p || board[i-1][j-1] == p || board[i-2][j] == p || 
                 board[i-1][j+1] == p || board[i-2][j-1] == p) return false;  
      }  

    /*
      00*
      000
      000
    */            
    if((j == 3 || j == 6 || j == 9) && (i == 1 || i == 4 || i == 7))
      {
         if(board[i][j-1] == p || board[i][j-2] == p || board[i+1][j] == p || 
             board[i+1][j-1] == p || board[i+1][j-2] == p || board[i+2][j] == p || 
                 board[i+2][j-1] == p || board[i+2][j-2] == p) return false;  
      } 

    /*
      000
      00*
      000
    */            
    if((j == 3 || j == 6 || j == 9) && (i == 2 || i == 5 || i == 8))
      {
         if(board[i-1][j] == p || board[i-1][j-1] == p || board[i-1][j-2] == p || 
             board[i][j-1] == p || board[i][j-2] == p || board[i+1][j] == p || 
                 board[i+1][j-1] == p || board[i+1][j-2] == p) return false;  
      }

    /*
      000
      000
      00*
    */            
    if((j == 3 || j == 6 || j == 9) && (i == 3 || i == 6 || i == 9))
      {
         if(board[i][j-1] == p || board[i][j-1] == p || board[i-1][j] == p || 
             board[i-1][j-1] == p || board[i-1][j-2] == p || board[i-2][j] == p || 
                 board[i-2][j-1] == p || board[i-2][j-2] == p) return false;  
      }      

    return true;                          
  }

void Sudoku::Help_Solve(int i, int j)
  {
    if(j <= 0) 
      {
        i = i-1;
        j = 9;
      }
    if(change[i][j] == 1) return Game.Help_Solve(i, j-1);
    for(int p = 1; p <= 9; p++)
      if(Game.Check_Conflicts(p, i, j)) 
        {
          board[i][j] = p;
          return;
        }
    return Game.Help_Solve(i, j-1);

  }

void Sudoku::Solve()
  {                          
      for(int i = 1; i <= 9; i++)
        {
          for(int j = 1; j <= 9; j++)
            {
              if(board[i][j] == 0 && change[i][j] == 0)
                {
                  Game.Help_Solve(i, j);           
                }      
            }      
        }

      for(int i = 1; i <= 9; i++)
        for(int j = 1; j <= 9; j++)
          if(board[i][j] == 0) Game.Help_Solve(i, j);

  }


int main()
{
  Game.Add_First_Cord();
  Game.Solve();
  Game.Print_Board();  

  system("pause");
  return 0;
}
