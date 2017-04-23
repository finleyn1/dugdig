#include "finl.h"
#include "dug.h"

int running = 1;
int dir;

void EventHandler(SDL_Event event);



int main(int argc, char *argv[])
{
	int i=0,j=0;
	SDL_Event event;

	dir =0;
	
	/****	music stuff, we'll worry about this later
	Mix_Music *music;
	Mix_Init(0);
	Mix_OpenAudio(MIX_DEFAULT_FREQUENCY,AUDIO_U8,2,1024);
	music = Mix_LoadMUS("atthezoo.mid");
	****/

	//initialize the screen, make sure this is called before any drawing is attempted
	InitScreen();


	//test building a sprite
	dug man(40,4,"spr/sprite.bmp");

	loadTex();
	InitMap();
	DrawBG();
	DrawTiles();
	SDL_UpdateRect(screen,0,0,0,0);

	SDL_EnableKeyRepeat(70,70);

	//DO NOT PLAY MUSIC ...yet
	//Mix_PlayMusic(music,-1);


	while(running)
	{
		dir =0;


		if(SDL_PollEvent(&event))
			EventHandler(event);


		if(dir!=0)
		{
			printf("%d\n",dir);
			man.move(dir);
		}
		DrawBG();
		DrawTiles();
		man.draw();
		SDL_UpdateRect(screen,0,0,0,0);
		SDL_Delay(50);
	}

}






void EventHandler(SDL_Event event)
{
	switch(event.type)
	{
		case SDL_QUIT:
			running =0;
			break;
		case SDL_KEYDOWN:
			switch(event.key.keysym.sym)
			{
				case SDLK_ESCAPE:
					running =0;
					break;
				case SDLK_SPACE:
					InitMap();
					break;
				case 'h':
					dir =1;	
					break;
				case 'l':
					dir = 2;
					break;
				case 'j':
					dir = 3;
					break;
				case 'k':
					dir = 4;
					break;
			}
			break;
	}	
}

