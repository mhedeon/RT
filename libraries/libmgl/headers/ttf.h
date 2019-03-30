#ifndef TTF_H
# define TTF_H

# include "libmgl.h"

TTF_Font *ttf_open_font(char *name, int size);
void ttf_close_font(TTF_Font *font);
void ttf_render_text(SDL_Renderer *ren, TTF_Font *font, SDL_Rect *r, char *text);


#endif
