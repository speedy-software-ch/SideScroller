#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL/SDL.h>

SDL_Surface *back;
SDL_Surface *black;
SDL_Surface *screen;
SDL_Surface *figure[8];
SDL_Surface *figure1[8];
SDL_Surface *kasten;

void DrawIMG();
int InitImages();
void DrawBG();

int xpos=0,ypos=0;
int done=0;
int frame=0;
int delay=0;
int lauf=0;
int kastenpos=0;
int height=330;
int jump=0;
int x=0;

int InitImages()
{
  back = SDL_LoadBMP("BG.bmp");
  black = SDL_LoadBMP("Black.bmp");
  figure[0] = SDL_LoadBMP("SideScrollerIMG00000.bmp");
  figure[1] = SDL_LoadBMP("SideScrollerIMG00001.bmp");
  figure[2] = SDL_LoadBMP("SideScrollerIMG00002.bmp");
  figure[3] = SDL_LoadBMP("SideScrollerIMG00003.bmp");
  figure[4] = SDL_LoadBMP("SideScrollerIMG00004.bmp");
  figure[5] = SDL_LoadBMP("SideScrollerIMG00005.bmp");
  figure[6] = SDL_LoadBMP("SideScrollerIMG00006.bmp");
  figure[7] = SDL_LoadBMP("SideScrollerIMG00007.bmp");
  figure1[0] = SDL_LoadBMP("RSideScrollerIMG00000.bmp");
  figure1[1] = SDL_LoadBMP("RSideScrollerIMG00001.bmp");
  figure1[2] = SDL_LoadBMP("RSideScrollerIMG00002.bmp");
  figure1[3] = SDL_LoadBMP("RSideScrollerIMG00003.bmp");
  figure1[4] = SDL_LoadBMP("RSideScrollerIMG00004.bmp");
  figure1[5] = SDL_LoadBMP("RSideScrollerIMG00005.bmp");
  figure1[6] = SDL_LoadBMP("RSideScrollerIMG00006.bmp");
  figure1[7] = SDL_LoadBMP("RSideScrollerIMG00007.bmp");
  kasten = SDL_LoadBMP("Kasten.bmp");
  return 0;
}
                
void DrawIMG(SDL_Surface *img, int x, int y)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_BlitSurface(img, NULL, screen, &dest);
}

void DrawIMG(SDL_Surface *img, int x, int y,
                                int w, int h, int x2, int y2)
{
  SDL_Rect dest;
  dest.x = x;
  dest.y = y;
  SDL_Rect dest2;
  dest2.x = x2;
  dest2.y = y2;
  dest2.w = w;
  dest2.h = h;
  SDL_BlitSurface(img, &dest2, screen, &dest);
}


void DrawBG()
{
DrawIMG(black,0,0);
  DrawIMG(back, xpos, 0);
  SDL_Flip(screen);
}


int main(int argc, char *argv[])
{
  Uint8* keys;
    if ( SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO) < 0 )
  {
    printf("Unable to init SDL: %s\n", SDL_GetError());
    exit(1);
  }
  atexit(SDL_Quit);
  screen=SDL_SetVideoMode(640,480,32,SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_FULLSCREEN);
  if ( screen == NULL )
  {
    printf("Unable to set 640x480 video: %s\n", SDL_GetError());
    exit(1);
  }
  InitImages();  
  DrawBG();
  while(done == 0)
  {
             DrawIMG(back,0,0);
    SDL_Event event;
    while ( SDL_PollEvent(&event) )
    {
      if ( event.type == SDL_QUIT )  {  done = 1;  }

      if ( event.type == SDL_KEYDOWN )
      {
        if ( event.key.keysym.sym == SDLK_ESCAPE ) { done = 1; }
        if ( event.key.keysym.sym ==SDLK_SPACE){ }
      }
    }
    keys = SDL_GetKeyState(NULL);
    if ( keys[SDLK_UP] ) {
         x=0;          
         if(height<=180)
         {
                        jump=1;
                        }
                        if(height==330)
                        {
                                       jump=0;
                                       } 
         if(jump==0)
         {
             height=height-1;
             
                                               SDL_SetColorKey(figure1[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure1[frame]->format, 0, 128, 128));
                                               DrawIMG(figure1[frame],10,height); 
                                                           
             }
             else
             {
                   height=height+1;
                                               SDL_SetColorKey(figure1[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure1[frame]->format, 0, 128, 128));
                                               DrawIMG(figure1[frame],10,height);
                 }
                  }
    if ( keys[SDLK_DOWN] ) { }
    if ( keys[SDLK_LEFT] ) {
                 delay++;
                       if(delay==5)
                       {
                                    delay=0;
                                    if(frame<6)
                                    {
                                               frame++;
                                               SDL_SetColorKey(figure[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure[frame]->format, 0, 128, 128));
                                               DrawIMG(figure[frame],10,330);
                                                           }
                        else
                        {
                            frame=0;
                            SDL_SetColorKey(figure[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure[frame]->format, 0, 128, 128));
                            DrawIMG(figure[frame],10,330);
                            }
                        }
                        }

    if ( keys[SDLK_RIGHT] ) {
         SDL_Flip(screen);
                          delay++;
                       if(delay==3)
                       {
                                   lauf++;
                                   if(lauf==20)
                                   {
                                               kastenpos=600;
                                               }
                                    delay=0;
                                    if(frame<6)
                                    {
                                               frame++;
                                               SDL_SetColorKey(figure1[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure1[frame]->format, 0, 128, 128));
                                               DrawIMG(figure1[frame],10,height);
                                               if(kastenpos<601&&kastenpos>0)
                                               {
                                                              kastenpos=kastenpos-20;
                                                              SDL_SetColorKey(kasten, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(kasten->format, 255, 255, 255));
                                                              DrawIMG(kasten,kastenpos,303);
                                                              }
                                                           }
                        else
                        {
                            frame=0;
                            SDL_SetColorKey(figure1[frame], SDL_SRCCOLORKEY, 
                           SDL_MapRGB(figure1[frame]->format, 0, 128, 128));
                            DrawIMG(figure1[frame],10,height);
                            if(kastenpos<601&&kastenpos>0)
                                               {
                                                              kastenpos=kastenpos-20;
                                                              SDL_SetColorKey(kasten, SDL_SRCCOLORKEY, 
                           SDL_MapRGB(kasten->format, 255, 255, 255));
                                                              DrawIMG(kasten,kastenpos,303);
                                                              }
                            }
                        }
                        }
                        
                        
    }
    return 0;
}
