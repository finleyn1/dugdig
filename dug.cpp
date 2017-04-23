#include "dug.h"

void dug::move(int direction) {
	switch(direction)
	{
		case 1:
			if(getY()*TILESIZE%GRIDSIZE==0)
			{
				if(getX()>0)
					{
						move(getX()-1,getY());
						setDir(1);
						Dig(getX(),getY(),getDir());
					}
			}
			else
			{
				if(getDir()==3 & getY()<HEIGHT/TILESIZE-SPRITESIZE/TILESIZE)
				{
					move(getX(),getY()+1);
					Dig(getX(),getY(),getDir());
				}
				if(getDir()==4 & getY()>0)
				{
					move(getX(),getY()-1);
					Dig(getX(),getY(),getDir());
				}

			}
			
			break;	
		case 2:
			if(getY()*TILESIZE%GRIDSIZE==0)
			{
				if(getX()<WIDTH/TILESIZE - SPRITESIZE/TILESIZE )
					{
						move(getX()+1,getY());
						setDir(2);
						Dig(getX(),getY(),getDir());
					}
			}
			else
			{
				if(getDir()==3 & getY()<HEIGHT/TILESIZE-SPRITESIZE/TILESIZE)
				{
					move(getX(),getY()+1);
					Dig(getX(),getY(),getDir());
				}
				if(getDir()==4 & getY()>0)
				{
					move(getX(),getY()-1);
					Dig(getX(),getY(),getDir());
				}

			}
			
			break;
		case 3:
			if(getX()*TILESIZE%GRIDSIZE==0)
			{
				if(getY()<HEIGHT/TILESIZE - SPRITESIZE/TILESIZE )
					{
						move(getX(),getY()+1);
						setDir(3);
						Dig(getX(),getY(),getDir());
					}
			}
			else
			{
				if(getDir()==2 & getX()<WIDTH/TILESIZE-SPRITESIZE/TILESIZE)
				{
					move(getX()+1,getY());
					Dig(getX(),getY(),getDir());
				}
				if(getDir()==1 & getX()>0)
				{
					move(getX()-1,getY());
					Dig(getX(),getY(),getDir());
				}

			}
			
			break;
		case 4:
			if(getX()*TILESIZE%GRIDSIZE==0)
			{
				if(getY()>0 )
					{
						move(getX(),getY()-1);
						setDir(4);
						Dig(getX(),getY(),getDir());
					}
			}
			else
			{
				if(getDir()==2 & getX()<WIDTH/TILESIZE-SPRITESIZE/TILESIZE)
				{
					move(getX()+1,getY());
					Dig(getX(),getY(),getDir());
				}
				if(getDir() ==1 & getX()>0)
				{
					move(getX()-1,getY());
					Dig(getX(),getY(),getDir());
				}
			}
			break;
	}
}

