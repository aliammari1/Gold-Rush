#include "header.h"
int main()
{
	SDL_Surface *screen=NULL;
	image bg;
	image iimage;
	image iiimage;
	image play;
	image settings;
	image quit;
	image bgs;
	image fs;
	image fsc;
	text t;
	SDL_Event event;
	int continuer = 1;
	int q=0,p=0,s=0;
	int musicP=1;
	int f=0;

	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER|SDL_INIT_AUDIO)!=0)
	{
		printf("Erreur :%s\n",SDL_GetError() );
	return 1;
	}


		screen=SDL_SetVideoMode(1280,639,32,SDL_HWSURFACE|SDL_DOUBLEBUF);
		if(screen==NULL)
	{
		printf("Erreur :%s\n",SDL_GetError() );
	return 1;
	}
	SDL_WM_SetCaption("GOLD RUSH",NULL);
	initImage(&bg,0,0,"download.jpg");
	initImage(&iimage,510,0,"11.jpg");
	initImage(&iiimage,1,523,"LOGO_GROUPE.png");
	initImage(&play,565,296,"PLAY.jpg");
	initImage(&settings,485,416,"SETTINGS.jpg");
	initImage(&bgs,0,0,"background_set.jpg");
	initImage(&quit,565,530,"QUIT.jpg");
	initImage(&fs,490,200,"FULLSCREEN.png");
	initImage(&fsc,490,200,"FULLSCREEN1.png");
	SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
	if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024)==-1)
    {
    	printf("%s\n",Mix_GetError());
    }	
    Mix_Music *music;
    music=Mix_LoadMUS("Background_music.mp3");
    Mix_PlayMusic(music,-1);
    int a,b,x,y;
    initText (&t);
while(continuer)
{

	SDL_BlitSurface(iimage.img,NULL,screen,&iimage.pos1);
	SDL_BlitSurface(iiimage.img,NULL,screen,&iiimage.pos1);
	SDL_BlitSurface(play.img,NULL,screen,&play.pos1);
	SDL_BlitSurface(settings.img,NULL,screen,&settings.pos1);
	SDL_BlitSurface(quit.img,NULL,screen,&quit.pos1);
	
	SDL_PollEvent(&event);
	
	switch(event.type)
	{
		case SDL_QUIT:
			continuer=0;
			break;
		case SDL_KEYDOWN:
			if(event.key.keysym.sym ==SDLK_ESCAPE)
				continuer = 0;
			if(event.key.keysym.sym ==SDLK_f)
			SDL_WM_ToggleFullScreen(screen);
				break;
		case SDL_MOUSEBUTTONDOWN:
			if(event.motion.x >= 565 && event.motion.x <= 723 && event.motion.y >= 296 && event.motion.y <= 366)
			{
				while(f==0)
				{
					SDL_BlitSurface(bgs.img,NULL,screen,&bgs.pos1);
					displayText(t,bgs.img);
					SDL_Event event1;
					while (SDL_PollEvent(&event1))
					{
						switch(event1.type)
						{
							case SDL_KEYDOWN:
								if (event1.key.keysym.sym==SDLK_e)
								{
									f=1;
								}
							break;
							}
							SDL_Flip(screen);
							}
							}
							}
			if(event.motion.x >= 565 && event.motion.x <= 700 && event.motion.y >= 530 && event.motion.y <= 630)
				continuer = 0;
			a=event.button.x;
			b=event.button.y;
			if(a >= 485 && a <= 849 && b >= 416 && b <= 486 && event.button.button==SDL_BUTTON_LEFT)
				{
				while(f==0)
				{
					SDL_BlitSurface(bgs.img,NULL,screen,&bgs.pos1);
					SDL_BlitSurface(fsc.img,NULL,screen,&fs.pos1);
					SDL_Event event2;
					while (SDL_PollEvent(&event2))
					{
						switch(event2.type)
						{
							case SDL_KEYDOWN:
								if (event2.key.keysym.sym==SDLK_r)
								{
									f=1;
								}
							break;
							case SDL_MOUSEMOTION:
							x=event2.motion.x;
							y=event2.motion.y;
							if (x > 490 && x < (490+250) && y > 200 && y < (200+36))
							SDL_BlitSurface(fs.img,NULL,screen,&fsc.pos1);
							break;
							case SDL_MOUSEBUTTONDOWN:
							a=event2.button.x;
							b=event2.button.y;
				if(a >= 490 && a <= (490+250) && b >= 200 && b <= 236 && event.button.button==SDL_BUTTON_LEFT)
					SDL_WM_ToggleFullScreen(screen);
					break;
						}
						SDL_Flip(screen);
					}
				}
				}
				break;
		case SDL_MOUSEMOTION:
			if(event.motion.x >= 565 && event.motion.x <= 723 && event.motion.y >= 530 && event.motion.y <= 600)
		{
		if(q == 0)
			SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
		initImage(&quit,565,530,"quit_c.png");
		q = 1;
		}
		else
		{
		if(q == 1)
		{
			SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
			q = 0;
		}
		initImage(&quit,565,530,"QUIT.jpg");		
		}
	
		if(event.motion.x >= 565 && event.motion.x <= 723 && event.motion.y >= 296 && event.motion.y <= 366)
		{
		if(p == 0)
			SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
		initImage(&play,565,296,"PLAY_C.png");
		p = 1;
		}
		else
		{
			if(p == 1)
			{
				SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
				p = 0;
			}
				
		initImage(&play,565,296,"PLAY.jpg");		
		}
		if(event.motion.x >= 485 && event.motion.x <= 849 && event.motion.y >= 416 && event.motion.y <= 486)
		{
		if(s == 0)
			SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
		initImage(&settings,475,410,"SETTINGS_C.png");
		s = 1;
		}
		else
		{
		if(s == 1)
		{
			SDL_BlitSurface(bg.img,NULL,screen,&bg.pos1);
			s = 0;
		}
		initImage(&settings,485,416,"SETTINGS.jpg");		
		}
		break;
		}
		
	SDL_Flip(screen);
}
	TTF_CloseFont(t.font);
	TTF_Quit();
	freeText(t);
	SDL_FreeSurface(bg.img);
	SDL_FreeSurface(iimage.img);
	SDL_FreeSurface(iiimage.img);
	SDL_FreeSurface(play.img);
	SDL_FreeSurface(quit.img);
	SDL_FreeSurface(settings.img);
	Mix_FreeMusic(music);
	SDL_Quit();
return 0;
}
