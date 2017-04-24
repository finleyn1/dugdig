#pragma once
#include "finl.h"

class sprite
{
	public:
		sprite();
		sprite(int x,int y,char *texture);
		~sprite();
		void draw(void);
		void move(int x,int y);

		int getX(void)
		{
			return x;
		}
		int getY(void)
		{
			return y;
		}
		int getDir(void)
		{
			return dir;
		}
		void setDir(int dir)
		{
			this->dir = dir;
		}


	private:
		void chooseFrame(int dir,int frame);
		void loadTexture(char *texture);

		//pointer to the sprite's surface in memory
		SDL_Surface *spr;

		//rectangles used for drawing in SDL
		//rcSprite is absolute pixel position and clip is for 
		//clipping from sprite sheet
		SDL_Rect rcSprite, rcClip;

		// x,y used to keep track of location on tilemap
		int x;
		int y;

		//the direction the sprite is facing
		//1=left,2=right,3=down,4=up
		int dir;
	

};
