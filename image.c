#include<SDL2/SDL.h>
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<SDL2/SDL_image.h>
#define MIN(a,b) (((a)<(b))?(a):(b))
void imageset(SDL_Texture* texture,SDL_Window* window,SDL_Renderer* renderer);
int  main()
{

	SDL_Window *window =NULL;
	SDL_Renderer* renderer  =NULL;
	
	if( SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf(" SDL_Init(SDL_INIT_VIDEO) error%S",SDL_GetError());
		return 1;
	}
	

	
	window= SDL_CreateWindow("window",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,800,800,SDL_WINDOW_FULLSCREEN_DESKTOP);
if( window == NULL ) {
		printf(" SDL_CreateWindow error%S",SDL_GetError());
		SDL_Quit();
		return 1;
	}

	renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if( renderer ==NULL ) {
		printf("SDL_CreateRenderer error%S",SDL_GetError());
		SDL_Quit();
		return 1;
	}
//*******************************************	
srand(time(NULL));	
	int imgFlags = IMG_INIT_JPG;
        if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}

	SDL_Event event_main;
	uint8_t running_main=1;
	SDL_Texture* texture=NULL;
	char* imagefile[3]={"1.jpg","2.jpg","3.jpg"};
	while(running_main)
	{
		while(SDL_PollEvent(&event_main))
		{
			switch(event_main.key.keysym.sym)
			{
				case SDLK_1:
					texture=IMG_LoadTexture(renderer,"1.jpg");
					if(texture == NULL){printf("IMG_LoadTexture%s",SDL_GetError());}
			
					break;
				case SDLK_2:
					texture=IMG_LoadTexture(renderer,"2.jpg");
					if(texture == NULL){printf("IMG_LoadTexture%s",SDL_GetError());}
					
					
					break;
				case SDLK_3:
					texture=IMG_LoadTexture(renderer,"3.jpg");
					if(texture == NULL){printf("IMG_LoadTexture%s",SDL_GetError());}
					break;
				case SDLK_4:
					texture=IMG_LoadTexture(renderer,imagefile[rand()%3]);
					if(texture == NULL){printf("IMG_LoadTexture%s",SDL_GetError());}
					break;
				case SDLK_q:
				case SDLK_ESCAPE:
					running_main=0;break;	
			}
			SDL_RenderClear(renderer);
			imageset(texture,window,renderer);
			SDL_RenderPresent(renderer);
		}
	}


	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}



void imageset(SDL_Texture* texture,SDL_Window* window,SDL_Renderer* renderer)
{
	int texture_w,texture_h;
	SDL_QueryTexture(texture,NULL,NULL,&texture_w,&texture_h);
	int window_w,window_h;
	SDL_GetWindowSize(window,&window_w,&window_h);
	int dstrect_x,dstrect_y,dstrect_w,dstrect_h;
	float times=MIN((float)window_w/texture_w,(float)window_h/texture_h);
	dstrect_w=(int)(texture_w*times);
	dstrect_h=(int)(texture_h*times);
	dstrect_x=(window_w-dstrect_w)/2;
	dstrect_y=(window_h-dstrect_h)/2;
	SDL_Rect dstrect={dstrect_x,dstrect_y,dstrect_w,dstrect_h};
	SDL_RenderCopy(renderer,texture,NULL,&dstrect);
}
