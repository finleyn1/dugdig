#ifndef FINL_H
#define FINL_H

#include "SDL.h"
//#include "SDL_mixer.h"

//horizontal and vertical pixel resolution
//make multiples of tilesize
#define WIDTH 480
#define HEIGHT 640

//size of each tile 
#define TILESIZE 8

//size of each grid space 
#define GRIDSIZE 32

//size of a sprite
#define SPRITESIZE 32

//WIDTH/TILESIZE * HEIGHT/TILESIZE
#define MAPSIZE 4800


extern SDL_Rect tileClip;
extern char tilemap[MAPSIZE];
extern SDL_Surface *tile;
extern SDL_Surface *screen;

void InitScreen(void);
void InitMap(void);
void DrawTiles(void);
void DrawBG(void);
void drawSprite(SDL_Surface *sprite,SDL_Rect *rcSprite,SDL_Rect *rcClip);
void loadTex(void);
void ChangeTile(int x, int y , int type);
void Dig(int x, int y, int dir);
int CheckGrid(int x, int y, int dir);
void loadMap(char *filename);
void ChangeGrid(int x,int y,int type);
int checkCollision(int aX,int aY,int bX,int bY);





#endif
