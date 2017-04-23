#include "foe.h"

void foe::move(void)
{
	int check =0;
	switch(getDir())
	{
		case 1:
		case 2:
			if(getY()*TILESIZE%GRIDSIZE==0)	//if we're square in a grid
				check = CheckGrid(getY(),getX(),getDir());
			break;
		case 3:
		case 4:
			if(getX()*TILESIZE%GRIDSIZE==0)
				check = CheckGrid(getY(),getX(),getDir());
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
		

	}
}
