test:
	g++ -c finl.c -L/usr/lib/i386-linux-gnu -lSDL -lSDL_mixer -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT 
	g++ -c main.cpp -L/usr/lib/i386-linux-gnu -lSDL -ISDL_mixer -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
	g++ -c sprite.cpp -L/usr/lib/i386-linux-gnu -lSDL -ISDL_mixer -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
	g++ -c dug.cpp -L/usr/lib/i386-linux-gnu -lSDL -ISDL_mixer -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT
	g++ *.o -o test -L/usr/lib/i386-linux-gnu -lSDL -ISDL_mixer -I/usr/include/SDL -D_GNU_SOURCE=1 -D_REENTRANT

