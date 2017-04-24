#include "foe.h"

void foe::move(void)
{
	int check =0;
	int i=0;
	switch(getDir())
	{
		case 1:
		case 2:
			if(getX()*TILESIZE%GRIDSIZE==0)	//if we're square in a grid
			{
				check = CheckGrid(getX(),getY(),3);
				check += CheckGrid(getX(),getY(),4);
				if(check==0)	//if both up and down are blocked
					check = CheckGrid(getX(),getY(),getDir());	//check if we can continue in current direction
				else
				{
					check =0;
					for(i=0;check==0&i<8;i++)
					{
					TargetPlayer();	//otherwise change direction based on target location
					check = CheckGrid(getX(),getY(),getDir());	//check if we can continue in current direction
					}
				}
			}
			else
				check=1;
			break;
		case 3:
		case 4:
			if(getY()*TILESIZE%GRIDSIZE==0)	//if we're square in a grid
			{
				check = CheckGrid(getX(),getY(),1);
				check += CheckGrid(getX(),getY(),2);
				if(check==0)	//if both up and down are blocked
					check = CheckGrid(getX(),getY(),getDir());	//check if we can continue in current direction
				else
				{
					check =0;
					for(i=0;check==0&i<8;i++)
					{
					TargetPlayer();	//otherwise change direction based on target location
					check = CheckGrid(getX(),getY(),getDir());	//check if we can continue in current direction
					}
				}
			}
			else
				check=1;
			break;
	}
	if(check==1)	// if we can move in this direction
	{
		switch(getDir())
		{
			case 1:
				move(getX()-1,getY());
				break;	
			case 2:
				move(getX()+1,getY());
				break;	
			case 3:
				move(getX(),getY()+1);
				break;	
			case 4:
				move(getX(),getY()-1);
				break;	
		}
	}
	else
	{
		switch(getDir())
		{
			case 1:
				setDir(2);
				move(getX()+1,getY());
				break;
			case 2:
				setDir(1);
				move(getX()-1,getY());
				break;
			case 3:
				setDir(4);
				move(getX(),getY()-1);
				break;
			case 4:
				setDir(3);
				move(getX(),getY()+1);
				break;
		}
	}
}

void foe::TargetPlayer(void)
{
	int delY;
	int delX;
	delX = getTx()-getX();	//delX negative means target is to left
	delY = getTy()-getY(); //delY negative means target is above

	switch(getDir())
	{
		case 1:
			if(delY>0)	//if target is below
				setDir(3);	//go down
			else if(delY<0)
				setDir(4);
			break;
		case 2:	
			if(delY>0)
				setDir(3);
			else if(delY<0)
				setDir(4);
			break;
		case 3:	
			if(delX>0)	//if target is to right
				setDir(2);	//go right
			else if(delX<0)
				setDir(1);
			break;
		case 4:	
			if(delX>0)	
				setDir(2);
			else if(delX<0)
				setDir(1);
			break;
	}
}
