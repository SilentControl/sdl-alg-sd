#include <iostream>
#include <cstdio>
#include "gameshell.h"

SDL_Surface* load_image(const char* filename);

gameshell::gameshell(const char* bgfilename)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,BPP,SDL_SWSURFACE);
	background = load_image(bgfilename);
	
	TTF_Init();
	SDL_Color green = {0x00,0xff,0x00};
	SDL_Color red = {0xff,0x00,0x00};
	SDL_Color yellow = {0xff,0xff,0x00};
	font = TTF_OpenFont("Orbitron_Black.ttf",30);
	win = TTF_RenderText_Solid(font,"WIN",green);
	lose = TTF_RenderText_Solid(font,"LOSE",red);
	tie = TTF_RenderText_Solid(font,"TIE",yellow);
	
	options[0] = load_image("scissors.bmp");
	options[1] = load_image("paper.bmp");
	options[2] = load_image("rock.bmp");
	options[3] = load_image("lizard.bmp");
	options[4] = load_image("spock.bmp");
	
	finalOptions[0] = load_image("scissors_orig.bmp");
	finalOptions[1] = load_image("paper_orig.bmp");
	finalOptions[2] = load_image("rock_orig.bmp");
	finalOptions[3] = load_image("lizard_orig.bmp");
	finalOptions[4] = load_image("spock_orig.bmp");
	
	Uint32 color = SDL_MapRGB(options[0]->format,0x00,0x00,0x00);
	for(int i=0;i<5;i++)
	{
		SDL_SetColorKey(options[i],SDL_SRCCOLORKEY,color);
		SDL_SetColorKey(finalOptions[i],SDL_SRCCOLORKEY,color);
		selected[i] = 0;
		hovered[i] = 0;
	}
	startRec.x = 70;
	startRec.y = 390;
	startRec.w = 100;
	startRec.h = 86;
	
	playerpos.x = 150;
	playerpos.y = 200;
	
	CPUpos.x = 350;
	CPUpos.y = 200;
	
	fontp1.x = 180;
	fontp1.y = 180;
	
	fontCPU.x = 380;
	fontCPU.y = 180;
	
	running = 1;
	gamestate = 1;
}

void gameshell::dehover()
{
	for(int i=0;i<5;i++)
		hovered[i] = 0;
}

void gameshell::deselect()
{
	for(int i=0;i<5;i++)
		selected[i] = 0;
}

void gameshell::dealpha(int x)
{
	if(x < -1 || x >= 5)
		return;
	if(x == -1)
		for(int i=0;i<5;i++)
			if(!selected[i])
				SDL_SetAlpha(options[i],SDL_SRCALPHA,255);
	else
		for(int i=0;i<5;i++)
			if(i!=x && !selected[i])
				SDL_SetAlpha(options[i],SDL_SRCALPHA,255);
}

void gameshell::show_options()
{
	SDL_Rect deplasare;
	deplasare.x = startRec.x;
	deplasare.y = startRec.y;
	
	for(int i=0;i<5;i++)
	{
		SDL_BlitSurface(options[i],NULL,screen,&deplasare);
		deplasare.x += 100;
	}
}

void gameshell::event_handler()
{
	SDL_Event event;
	//int start = SDL_GetTicks();
	int xmouse;
	int ymouse;
	while(SDL_PollEvent(&event))
	{
		if(gamestate == 0)
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = 0;
				break;
			}
		}
		else
		{
			switch(event.type)
			{
				case SDL_QUIT:
					running = 0;
				break;
			
				case SDL_MOUSEMOTION:
			//	std::cout<<"(x,y) = "<<event.motion.x<<" "<<event.motion.y<<"\n";
					xmouse = event.motion.x;
					ymouse = event.motion.y;
					for(int i=0;i<5;i++)
						if(xmouse > startRec.x + i*100 && xmouse < startRec.x +i*100 + 83 && ymouse > startRec.y && ymouse < startRec.y + startRec.h)
						{
							hovered[i] = 1;
							break;
						}
						else
							dehover();
				//for(int i=0;i<5;i++)
					//std::cout<<hovered[i]<<" ";
			//	std::cout<<"\n";
				break;
			
				case SDL_MOUSEBUTTONDOWN:
					xmouse = event.motion.x;
					ymouse = event.motion.y;
					for(int i=0;i<5;i++)
						if(xmouse > startRec.x + i*100 && xmouse < startRec.x +i*100 + 83 && ymouse > startRec.y && ymouse < startRec.y + startRec.h)
						{
							deselect();
							selected[i] = 1;
							break;
						}
					else
						deselect();
					for(int i=0;i<5;i++)
						std::cout<<selected[i]<<" ";
					std::cout<<"\n";
				break;	
			}
		}
	}
}

void gameshell::action()
{
	running = 1;
	while(running)
	{
		int start = SDL_GetTicks();
		event_handler();
		for(int i=0;i<5;i++)
		{
			if(selected[i] || hovered[i])
			{
				SDL_SetAlpha(options[i],SDL_SRCALPHA,128);
				dealpha(i);
			}
			else
			if(!selected[i] && !hovered[i])
				SDL_SetAlpha(options[i],SDL_SRCALPHA,255);
		}
		
		for(int i=0;i<5;i++)
		{
			if(selected[i])
			{
				SDL_BlitSurface(finalOptions[i],NULL,screen,&playerpos);	
				int CPU_PICK = rand()%5;
				std::cout<<"CPU_PICK "<<CPU_PICK<<"\n";
				deselect();
				SDL_BlitSurface(finalOptions[CPU_PICK],NULL,screen,&CPUpos);
				SDL_Flip(screen);
				SDL_Delay(2000);
				if(matrix[i][CPU_PICK] == 1)
				{
					SDL_BlitSurface(win,NULL,screen,&fontp1);
					SDL_BlitSurface(lose,NULL,screen,&fontCPU);
				}
				
				else
				if(matrix[i][CPU_PICK] == 2)
				{
					SDL_BlitSurface(tie,NULL,screen,&fontp1);
					SDL_BlitSurface(tie,NULL,screen,&fontCPU);
				}
				else
				if(matrix[i][CPU_PICK] == 0)
				{
					SDL_BlitSurface(lose,NULL,screen,&fontp1);
					SDL_BlitSurface(win,NULL,screen,&fontCPU);
				}
				SDL_Flip(screen);
				SDL_Delay(2000);
			}
		}
		
		
		SDL_BlitSurface(background,NULL,screen,NULL);
		show_options();
		SDL_Flip(screen);
		
		if(1000/FPS > SDL_GetTicks() - start)
		{
			SDL_Delay(1000/FPS - (SDL_GetTicks() - start));
		}
	}
}

gameshell::~gameshell()
{
	SDL_FreeSurface(background);
	for(int i=0;i<5;i++)
	{
		SDL_FreeSurface(options[i]);
		SDL_FreeSurface(finalOptions[i]);
	}
	SDL_Quit();
	std::cout<<"Destructed\n";
}
