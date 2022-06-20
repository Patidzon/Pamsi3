#include <iostream>
#include <fstream>
#include <math.h>
#include <chrono>
#include <cstring>
//#include <algorithm>
//#include<bits/stdc++.h>
using namespace std;

class plansza
{
private:
    char ** adj;
    int rozmiar,wartosc,bmr,bmc;
public:
    plansza(int rozmiar,int wartosc)
    {
    this->rozmiar=rozmiar;
    this->wartosc=wartosc;
            adj=new char*[rozmiar];
            for (int r = 0; r < rozmiar; r++)
            {
                adj[r]=new char[rozmiar];
                for (int c = 0; c < rozmiar; c++)
                {
                    adj[r][c]=' ';
                }
            }   
    }
    void wypisz()
    {       
            cout<<"  ";
            for (int i = 0; i < rozmiar; i++)
            {
              cout<<i<<" ";
            }
            cout<<endl;
            for (int i = 0; i < rozmiar; i++)
            {   
                cout<<i<<" ";
                for (int j = 0; j < rozmiar; j++)
                {   
                    cout<<adj[i][j]<<" ";
                }
                cout<<endl;
            }  
    }
    bool zaznacz(int row, int column,int nr_gracza)
    {  
         if (column>=rozmiar||row>=rozmiar)
    {
       cout<<"nie poprawne pole"<<endl;
            return false;
    }
    
        char znak;
        if (nr_gracza==1)
        {
            znak='o';
        }
        else
        {
            znak='x';
        }
        if (adj[row][column]!='o'&&adj[row][column]!='x')
        {
            adj[row][column]=znak;
            return true;
        }
        else
        {
            cout<<"pole zajete"<<endl;
            return false;
        }
    }
    bool findspot()
    {
        for (int i = 0; i < rozmiar; i++)
        {
            for (int j = 0; j < rozmiar; j++)
            {
               if (adj[i][j]==' ')
               {
                return true;
               }
            } 
        }
    return false;     
        
    }
     
    bool check(int nr_gracza)
    {
        char znak;
        int strike=0;
        int f=0,g=0;
        if (nr_gracza==1)
        {
            znak='o';
        }
        else
        {
            znak='x';
        }
        
        for (int i = 0; i < rozmiar; i++)
        {
            strike=0;
            for (int j = 0; j < rozmiar; j++)
            {
               if (adj[i][j]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               
               
            }
            
        }
         strike=0;
        for (int i = 0; i < rozmiar; i++)
        {
            strike=0;
            for (int j = 0; j < rozmiar; j++)
            {
               if (adj[j][i]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               
               
            }
            
        }
         strike=0;
        for (int i = rozmiar-wartosc; i >0; i--)
        {
            f=0;
            strike=0;
            for (int j = 0; j <wartosc+g ; j++)
            {   //adj[i-f][j]=znak;
               if (adj[i-f][j]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               f--;
            }
            g++;
        }
        
        g=0;
         strike=0;
        for (int j = 0; j <=rozmiar-wartosc; j++)
        {
            f=0;
            strike=0;
            for (int i = 0; i <rozmiar-g ; i++)
            {   //adj[i][j-f]=znak;
               if (adj[i][j-f]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               f--;
            }
            g++;
        }
        g=0;
         strike=0;
       for (int j = wartosc-1; j <rozmiar; j++)
        {
            f=0;
            strike=0;
        for (int i = 0; i <wartosc+g ; i++)
            {   //adj[i][j-f]=znak;
               if (adj[i][j-f]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               f++;
            }
            g++;
        }
        g=0;
         strike=0;
        for (int i = 1; i <=rozmiar-wartosc; i++)
        {
            f=0;
            strike=0;
        for (int j = rozmiar-1; j >g ; j--)
            {   //adj[i+f][j]=znak;
    
               if (adj[i+f][j]==znak)
               {
                   strike++;
                   if (strike==wartosc)
                   {
                       return true;
                   }
               }
               else
               {
                   strike=0;
               }
               f++;
            }
            g++;
        }
         strike=0;
        return false;
    }
    int evaluate()
    {
        if(check(1))
        {
            return +10;
        }
             if(check(2))
        {
            return -10;
        }
        return 0;
    }
    int minimax( int depth, bool isMax)
{
	int score = evaluate();


	if (score == 10)
		return score;

	if (score == -10)
		return score;

	if (findspot()==false)
		return 0;

	if (isMax)
	{
		int best = -1000;

		for (int i = 0; i<rozmiar; i++)
		{
			for (int j = 0; j<rozmiar; j++)
			{
			
				if (adj[i][j]==' ')
				{
					
					adj[i][j] = 'o';

				
					best = max( best,
						minimax( depth+1, !isMax) );

				
					adj[i][j] = ' ';
				}
			}
		}
		return best;
	}


	else
	{
		int best = 1000;

	
		for (int i = 0; i<rozmiar; i++)
		{
			for (int j = 0; j<rozmiar; j++)
			{
				
				if (adj[i][j]==' ')
				{
				
					adj[i][j] = 'x';

			
					best = min(best,
						minimax( depth+1, !isMax));

				
					adj[i][j] = ' ';
				}
			}
		}
		return best;
	}
}
void findBestMove()
{
	int bestVal = -1000;

    bmr=-1;
    bmc=-1;


	for (int i = 0; i<rozmiar; i++)
	{
		for (int j = 0; j<rozmiar; j++)
		{
		
			if (adj[i][j]==' ')
			{
		
				adj[i][j] = 'o';

				
				int moveVal = minimax( 0, false);

		
				adj[i][j] = ' ';

			
				if (moveVal > bestVal)
				{
					bmr = i;
					bmc = j;
					bestVal = moveVal;
				}
			}
		}
	}

	/*printf("The value of the best Move is : %d\n\n",
			bestVal);
    printf("ROW: %d COL: %d\n\n", bmr,
								bmc );
*/
}
void gra()
{
    while (findspot()==true)
    {int a,b;
       if (check(2))
       {
           cout<<"wygral gracz"<<endl;
          return;
       }
           if (check(1))
       {
           cout<<"wygral komputer"<<endl;
          return;
       }
    wypisz();
    cout<<"podaj pole"<<endl;
    cin>>a;
    cin>>b;
    zaznacz(a,b,2);
    wypisz();
    if(findspot())
    {
    findBestMove();
    zaznacz(bmr,bmc,1);
    wypisz();
    }
    }
   cout<<"remis"<<endl; 
}
void reset()
{
for (int r = 0; r < rozmiar; r++)
        {
            adj[r]=new char[rozmiar];
            for (int c = 0; c < rozmiar; c++)
            {
                adj[r][c]=' ';
            }
        }   
}
};
int main()
{
int arg1,arg2,arg3=0,arg4=0;
while(arg4!=1)
{   arg3=0;
    cout<<"podaj rozmiar pola"<<endl;
    cin>>arg1;
    cout<<"podaj ilosc znakow do zwyciestwa "<<endl;
    cin>>arg2;
    plansza p1(arg1,arg2);
   while (arg3!=1)
    {
        p1.gra();
        cout<<"nacisnij 0 aby powtorzyc"<<endl
        <<"nacisnij 1 aby zakonczyc"<<endl;
        cin>>arg3;
        p1.reset();
    }
    cout<<"nacisnij 0 aby zmienic parametru"<<endl
    <<"nacisnij 1 aby zakonczyc"<<endl;
     cin>>arg4;
}
return 0;
}
