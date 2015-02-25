#ifndef _SDLIMG_JPEG_
#define _SDLIMG_JPEG_


#ifdef ___NDLESS___

#include "SDL/SDL.h"
#include "SDL/SDL_version.h"
#include "SDL/begin_code.h"

int     SDLIMG_InitJPG();
void    SDLIMG_QuitJPG();
int     SDLIMG_InitPNG();
void    SDLIMG_QuitPNG();

#define SDLIMG_Init()       {SDLIMG_InitJPG();SDLIMG_InitPNG();}
#define SDLIMG_Quit()       {SDLIMG_QuitJPG();SDLIMG_QuitPNG();}

extern DECLSPEC int SDLCALL SDLIMG_isJPG(SDL_RWops *src);
extern DECLSPEC SDL_Surface * SDLCALL SDLIMG_LoadJPG_RW(SDL_RWops *src);

extern DECLSPEC int SDLCALL SDLIMG_isPNG(SDL_RWops *src);
extern DECLSPEC SDL_Surface * SDLCALL SDLIMG_LoadPNG_RW(SDL_RWops *src);

#define SDLIMG_SetError	SDL_SetError
#define SDLIMG_GetError	SDL_GetError

#include "SDL/close_code.h"

#define LOAD_JPEG
#define LOAD_PNG

#else

#include "SDL/SDL_image.h"

#define SDLIMG_Init()       IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG)
#define SDLIMG_Quit()       IMG_Quit()

#define SDLIMG_LoadJPG_RW     IMG_LoadJPG_RW
#define SDLIMG_isJPG          IMG_isJPG
#define SDLIMG_LoadPNG_RW     IMG_LoadPNG_RW
#define SDLIMG_isPNG          IMG_isPNG

#endif /* __NDLESS__ */

#endif /* _OIMG_JPEG_ */
