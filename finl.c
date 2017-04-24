#include "finl.h"
#include <stdio.h>


SDL_Rect tileClip;
char tilemap[MAPSIZE];
SDL_Surface *tile;
SDL_Surface *screen;


void InitScreen(void)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_WM_SetCaption("TilingTest","TilingTest");
	screen = SDL_SetVideoMode(WIDTH,HEIGHT,0,0);
}

void InitMap(void)
{
	int i=0;
	int j=0;
	for(i=0;i<HEIGHT/TILESIZE;i++)
		for(j=0;j<WIDTH/TILESIZE;j++)
			tilemap[i*WIDTH/TILESIZE+j] = 0; 
			//init all tiles to undug
}

void loadMap(char *filename)
{
	int i=0;
	int j=0;
	int type=0;
	FILE *infile = fopen(filename,"r");
	if(infile==NULL)
		return;
	
	for(i=0;i<HEIGHT/GRIDSIZE;i++)
	{
		for(j=0;j<WIDTH/GRIDSIZE;j++)
		{
			type = fgetc(infile);
			type-='0';
			ChangeGrid(j,i,type);
		}
	}
	fclose(infile);
}

int checkCollision(int aX,int aY,int bX,int bY) //check if a collides with b
{
	if(aX+SPRITESIZE/TILESIZE >bX & aX+1 < bX+SPRITESIZE/TILESIZE & aY+SPRITESIZE/TILESIZE > bY  & aY+1 <bY+SPRITESIZE/TILESIZE)
		return 1;
	return 0;
}

void ChangeGrid(int x,int y,int type)
{
	int i=0;
	int j=0;

	y*=GRIDSIZE/TILESIZE;
	x*=GRIDSIZE/TILESIZE;
	
	for(i=0;i<GRIDSIZE/TILESIZE;i++)
		for(j=0;j<GRIDSIZE/TILESIZE;j++)
			switch(type)
			{	
				case 1:
					switch(j)
					{
						case 0:
							ChangeTile(x+i,y+j,2);
							break;
						case 1:
						case 2:
							ChangeTile(x+i,y+j,1);
							break;
						case 3:
							ChangeTile(x+i,y+j,3);
							break;
					}	
					break;
				default:
					//ChangeTile(x*TILESIZE+i,y*TILESIZE+j,0);
					break;
			}

}



//load textures from BMPS
//call before any onscreen drawing
void loadTex(void)
{
	SDL_Surface *temp;





	temp = SDL_LoadBMP("spr/tiles.bmp");
	tile = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	tileClip.x=0;
	tileClip.y=0;
	tileClip.w=8;
	tileClip.h=8;
	
}

void drawSprite(SDL_Surface *sprite,SDL_Rect *rcSprite,SDL_Rect *rcClip)
{
	SDL_BlitSurface(sprite,rcClip,screen,rcSprite);
}



//change what 'type' a tile is
//0 is dirt, 1 is blank
//2-5 are wall tiles top,bottom,left right
//the rest are corners, currently not implemented in this version of code
void ChangeTile(int x, int y , int type)
{
	tilemap[y*WIDTH/TILESIZE+x] = type;
}


//1 = left 2=right 3=down 4=up
//Dig out tiles based on location and direction of player
void Dig(int x, int y ,int dir)
{
	int i=0;
	int j=0;	
	int check;	
	for(j=0;j<2;j++)
		for(i=0;i<4;i++)
		{
			switch(dir)
			{
				case 1:
					check = tilemap[(y+i)*WIDTH/TILESIZE+x+j];
					if(i==1 | i==2 | check==1| check==4 | check==5)
						ChangeTile(x+j,y+i,1);
					else if(i==0 & check==0)
						ChangeTile(x+j,y+i,2);
					else if(check==0)
						ChangeTile(x+j,y+i,3);
					break;
				case 2:
					check = tilemap[(y+i)*WIDTH/TILESIZE+x+SPRITESIZE/TILESIZE-1-j];
					if(i==1 | i==2 | check==1 | check==4 | check==5)
						ChangeTile(x+SPRITESIZE/TILESIZE-1-j,y+i,1);
					else if(i==0 & check==0)
						ChangeTile(x+SPRITESIZE/TILESIZE-1-j,y+i,2);
					else  if(check==0)
						ChangeTile(x+SPRITESIZE/TILESIZE-1-j,y+i,3);
					break;
				case 3:
					check = tilemap[(y+SPRITESIZE/TILESIZE-1-j)*WIDTH/TILESIZE+x+i];
					if(i==1|i==2 | check==1 | check == 2 | check ==3)
						ChangeTile(x+i,y+SPRITESIZE/TILESIZE-1-j,1);
					else if(i==0 | & check==0)
						ChangeTile(x+i,y+SPRITESIZE/TILESIZE-1-j,4);
					else if(check==0)
						ChangeTile(x+i,y+SPRITESIZE/TILESIZE-1-j,5);
					break;
				case 4:
					check = tilemap[(y+j)*WIDTH/TILESIZE+x+i];
					if(i==1|i==2 | check==1 | check ==2 | check ==3)
						ChangeTile(x+i,y+j,1);
					else if(i==0 & check ==0)
						ChangeTile(x+i,y+j,4);
					else if(check==0)
						ChangeTile(x+i,y+j,5);
					break;
			}
		}

}

//check the Grid space to see if the ai can pass through it in a valid way
int CheckGrid(int x, int y, int dir)
{
	int i=0;
//	int j=0;
	int check =1;

	//'snap' to the nearest grid space
	x/=(GRIDSIZE/TILESIZE);
	y/=(GRIDSIZE/TILESIZE);


	//going right or down, check the grid beyond
	//(this corrects for sprite's size)
	if(dir==2)
		x+=1;
	if(dir==3)
		y+=1;
	


	if(x>WIDTH/TILESIZE | y>HEIGHT/TILESIZE) //if out of bounds break
		return 0;

	//convert back to 'tile coordinates'	
	x*=GRIDSIZE/TILESIZE;
	y*=GRIDSIZE/TILESIZE;	


	/***	debug print	
	printf("(%d,%d),dir:%d\n",x,y,dir);
	for(i=0;i<GRIDSIZE/TILESIZE;i++)
	{
		for(j=0;j<GRIDSIZE/TILESIZE;j++)
			printf("%d ", tilemap[(y+i)*WIDTH/TILESIZE+(x+j)]);

		putchar('\n');
	}
	***/
	
	//check  3 tiles from the direction approached to see if it's passable	
	for(i=0;i<4 & check==1 ;i++)
	{
		switch(dir)	//check different depending on which direction
		{
			case 1:
				check = tilemap[(y+2)*(WIDTH/TILESIZE) + x+2-i];
				break;
			case 2:
				check = tilemap[(y+2)*(WIDTH/TILESIZE) + x+i-1];
				break;
			case 3:
				check = tilemap[(y+i-1)*(WIDTH/TILESIZE) + x+2];
				break;
			case 4:
				check = tilemap[(y+2-i)*(WIDTH/TILESIZE) + x+2];
				break;
		}
	}
	if(check!=1) //if we didn't hit an impassable block, return a 1
		return 0;
	else 
		return 1;
}


//draw all tunnel tiles on screen
//call in main, after updating background and before updating sprites
void DrawTiles(void)
{
	int i=0;
	int j=0;
	SDL_Rect box;
	for(i=0;i<HEIGHT/TILESIZE;i++)
		for(j=0;j<WIDTH/TILESIZE;j++)
		{
			//what type of tile to draw
			switch(tilemap[i*WIDTH/TILESIZE+j]) 
			{
				case 1:
					tileClip.x=0;
					tileClip.y=0;
					break;
				case 2:
					tileClip.x=TILESIZE;
					tileClip.y=0;
					break;
				case 3:
					tileClip.x=TILESIZE*2;
					tileClip.y=0;
					break;
				case 4:
					tileClip.x=TILESIZE;
					tileClip.y=TILESIZE;
					break;
				case 5:
					tileClip.x=TILESIZE*2;
					tileClip.y=TILESIZE;
					break;
				case 6:
					tileClip.x=TILESIZE*3;
					tileClip.y=0;
					break;
				case 7:
					tileClip.x=TILESIZE*4;
					tileClip.y=0;
					break;
				case 8:
					tileClip.x=TILESIZE*3;
					tileClip.y=TILESIZE;
					break;
				case 9:
					tileClip.x=TILESIZE*4;
					tileClip.y=TILESIZE;
					break;
				case 10:
					tileClip.x=TILESIZE*5;
					tileClip.y=0;
					break;
				case 11:
					tileClip.x=TILESIZE*6;
					tileClip.y=0;
					break;
				case 12:
					tileClip.x=TILESIZE*5;
					tileClip.y=TILESIZE;
					break;
				case 13:
					tileClip.x=TILESIZE*6;
					tileClip.y=TILESIZE;
					break;
				default:
					continue;
					break;
				
			}
			box.x=j*TILESIZE;
			box.y=i*TILESIZE;
			SDL_BlitSurface(tile,&tileClip,screen,&box);
		}

}


//Draws the background for the map
//call first when redrawing screen
void DrawBG(void)
{
	int i=0,j=0;
	SDL_Rect box;
	tileClip.x=0;
	tileClip.y=TILESIZE;
	for(i=0;i<HEIGHT/TILESIZE;i++)
		for(j=0;j<WIDTH/TILESIZE;j++)
		{
			box.x=j*TILESIZE;
			box.y=i*TILESIZE;
			SDL_BlitSurface(tile,&tileClip,screen,&box);
		}

}
