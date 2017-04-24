#pragma once
#include "finl.h"
#include "sprite.h"

class foe : public sprite
{
	public:
		using sprite::move;
		foe();

		foe(int x,int y,char *texture) : sprite(x,y,texture)
		{
			setTarget(0,0);
		};
		void setTarget(int x,int y)
		{
			targetX=x;
			targetY=y;
		}
		int getTx(void)
		{
			return targetX;
		}
		int getTy(void)
		{
			return targetY;
		}

		void move(void);
	private:
		void TargetPlayer(void);
		int targetX;	
		int targetY;
};
