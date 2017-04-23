#pragma once
#include "finl.h"
#include "sprite.h"

class dug : public sprite
{
	public:
		using  sprite::move;

		dug(int x,int y,char *texture) : sprite(x,y,texture)
		{

		};
		void move(int direction);
	private:
	

};
