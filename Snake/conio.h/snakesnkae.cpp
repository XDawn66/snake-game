#include<iostream>
#include <cstdlib>
#include "conio.h"

enum Direction{ STOP = 0, LEFT, RIGHT, UP, DOWN, END};
bool gamestop = false;

class snake
{
  public:
  void createmap(snake &a);
  void update(snake &a);
  void input();
  void print(snake a);
  private:  
  int x,y,width,length,score;
  int fruitx,fruity;
  Direction dir;
  std::string map[40][40];
  int ntail;
  int tailx[100];
  int taily[100];
};


void snake::createmap(snake &a)
{
    a.width = 40;
    a.length = 40;
    a.x = width/2;
    a.y = length/2;
    a.fruitx = rand() % width;
    a.fruity = rand() % length;
    a.ntail = 0;
    //std::cout<<"work\n"; 
    for(int z = 0; z < length; z++) //the bar for top and bottom
    {
        a.map[0][z] = "#"; //top
        a.map[width-1][z] = "#"; //bottom
    }

    for(int i = 1; i < width-1; i++) //starting from the first line
    {
        for(int j = 0; j < length; j++)
        {
            if(j == 0 || j == length-1) //when at the first block or the last block
            {
                a.map[i][j] = "#";
            }
            else if(i == a.fruity && j == a.fruitx) //when at the fruit postion
            {
               a.map[i][j] = "F";
            }
            else if(i == a.y && j == a.x) //snake postition
            {
                a.map[i][j] = "O";
            }
            else
            {
                bool printtail = false;
               
                if(!printtail)
                {
                    a.map[i][j] = " ";
                }
            }
        }
    }

}

void snake::print(snake a) //this function is used to print the map and the snake in each loop
{
     for(int i = 0; i < a.width; i++)
    {
        for(int j = 0; j < a.length; j++)
        {
           std::cout<<a.map[i][j];
        }
        std::cout<<std::endl;
    }
   // std::cout<<"x: "<<x<<std::endl;
    //std::cout<<"y: "<<y<<std::endl;
    //std::cout<<"width: "<<a.width<<std::endl;
    //std::cout<<"length: "<<a.length<<std::endl;
   // std::cout<<"fruitx: "<<a.fruitx<<std::endl;
   // std::cout<<"fruity: "<<a.fruity<<std::endl;
     std::cout<<"scroe: "<<a.score<<std::endl;
     int count = 0;
     int count2 = 0;
   //std::cout<<"tailx: ";
   	for(int c = 0; c<a.ntail;c++)
      { 
      	std::cout<<a.tailx[c]<< " ";
      	}
      std::cout<<std::endl;
      //std::cout<<"taily ";
      for(int d = 0; d<a.ntail;d++)
      {
      std::cout<<a.taily[d]<<" ";
      }
       std::cout<<std::endl;
}

void snake::input()
{
    if(_kbhit())
    {
        switch(getch()) //using AWDS to control the snake
        {
            case 'a':
            {
                dir = LEFT;
                break;
            }
            case 's':
            {
                dir = DOWN;
                break;
            }
            case 'd':
            {
                dir = RIGHT;
                break;
            }
            case 'w':
            {
                dir = UP;
                break;
            }
            case 'x':
            {
                dir = END;
            }
        }
    }
}

void snake::update(snake &a)
{
   
    for(int u = 1; u<a.length-1; u++)
    {
	for(int l = 1; l<a.width-1; l++)
	{
		for(int c = 0; c<a.ntail; c++)
		{
			if(u!= tailx[c] && l!= taily[c] )
			{
				a.map[u][l] = " ";
			}
			if(a.x == tailx[c] && a.y == taily[c])
			{
				gamestop = true;
			}
		}
		if(u!=a.fruitx && l!=a.fruity)
		{
		 	a.map[u][l] = " ";
		}
		if(u!=a.x && l!=a.y)
		{
			a.map[u][l] = " ";
		}
	}
    }
     a.map[a.fruity][a.fruitx] = "F"; //setting the fruit point
    if(a.x == a.fruitx && a.y == a.fruity)
    {
        a.score +=10;
        a.fruitx = rand() % a.width;
        a.fruity = rand() % a.length;
        a.map[a.fruity][a.fruitx] = "F";
        a.ntail++;
    }
    
    int firstx,firsty,secondx,secondy; 
  

    firstx = a.tailx[0];
    firsty = a.taily[0];
    
    a.tailx[0] = a.x; //the zeroth tail, the head
    a.taily[0] = a.y;
   
    for(int i = 1; i < a.ntail; i++)
    {
        secondx = a.tailx[i];
        secondy = a.taily[i];
        a.tailx[i] = firstx;
        a.taily[i] = firsty;
        firstx = secondx;
        firsty = secondy;
    }
    
    //a.map[a.y][a.x] = " "; //turn the original space into nothing
    
  	for(int z = 0; z<a.ntail; z++)
        {
        	int tempx = a.tailx[z];
        	int tempy = a.taily[z];
         	a.map[tempy][tempx] = "o";
      	}	

    
    switch(a.dir)
    {
       case LEFT:
       {
            a.x--;
            break;
       }
       case RIGHT:
       {
            a.x++;
            break;
       }
       case DOWN:
       {
            a.y++;
            break;
       }
       case UP:
       {
            a.y--;
            break;
       }
       case END:
       {
	    gamestop = true;
	    break;
	}
	
    }
    
    if(a.x>a.width-1 || a.x<1 || a.y >a.length-1 || a.y < 1)
    {
	gamestop = true;
    }
    
    a.map[a.y][a.x] = "O"; //update the head
     
}

int main()
{
    snake s;
    s.createmap(s);
    while(!gamestop)
    {
    	system("clear");
    	s.input();
        s.update(s);
        s.print(s);
        sleep(1);
    }
    
}
