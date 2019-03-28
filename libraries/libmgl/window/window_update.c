#include "libmgl.h"

void			upd_win(t_window *win)
{
	SDL_UpdateTexture(win->tex, NULL, win->buff,
		win->w * sizeof(Uint32));
	SDL_RenderClear(win->ren);
	SDL_RenderCopy(win->ren, win->tex, NULL, NULL);
	SDL_RenderPresent(win->ren);
}

void			upd_area_tex(t_window *win, SDL_Rect *r)
{
	SDL_UpdateTexture(win->tex, r, win->buff,
		win->w * sizeof(Uint32));
	SDL_RenderClear(win->ren);
	SDL_RenderCopy(win->ren, win->tex, NULL, NULL);
	SDL_RenderPresent(win->ren);
}

void			upd_area_ren(t_window *win, SDL_Rect *r)
{
	SDL_UpdateTexture(win->tex, NULL, win->buff,
		win->w * sizeof(Uint32));
	SDL_RenderClear(win->ren);
	SDL_RenderCopy(win->ren, win->tex, r, r);
	SDL_RenderPresent(win->ren);
}
