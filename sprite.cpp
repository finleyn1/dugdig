#include "sprite.h"

sprite::sprite(int x,int y, char *texture)
{
	loadTexture(texture);
	
	dir = 1;

	//set to the pixel locations for x/y
	move(x,y);

	//set size of sprite
	rcSprite.w = rcSprite.h = SPRITESIZE; 

	//set sprite clipping rect to first sprite
	chooseFrame(dir,0);

	//initialize size of clipping box
	rcClip.h = rcClip.w = SPRITESIZE;
}


sprite::~sprite()
{
	//free up the surface for this sprite
	SDL_FreeSurface(spr);
}

void sprite::move(int x,int y)
{
	this->x = x;
	this->y = y;
	rcSprite.x = x*TILESIZE;
	rcSprite.y = y*TILESIZE; 
}

void sprite::draw(void)
{
	drawSprite(spr,&rcSprite,&rcClip);
}

void sprite::chooseFrame(int dir,int frame)
{
	//different rows for sprite represent different
	//directions 
	rcClip.y = (dir-1)*TILESIZE;

	//different columns in spritesheet
	rcClip.x = SPRITESIZE*frame;
}

void sprite::loadTexture(char *texture)
{
	SDL_Surface *temp;
	int colorkey;

	//load texture and free temp pointer	
	temp = SDL_LoadBMP(texture);
	spr = SDL_DisplayFormat(temp);
	SDL_FreeSurface(temp);

	colorkey = SDL_MapRGB(screen->format,255,0,255);	//key out magenta
	SDL_SetColorKey(spr,SDL_SRCCOLORKEY|SDL_RLEACCEL,colorkey);
}


