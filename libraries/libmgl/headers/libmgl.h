#ifndef LIBMGL_H
# define LIBMGL_H

/*
**	Dynamic checking of Operating System
*/
# ifndef _APPLE_
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
#  include "SDL_mixer.h"
# elif _WIN32
#  include <SDL.h>
#  include <SDL_image.h>
#  include <SDL_ttf.h>
#  include <SDL_mixer.h>
# elif _linux_
#  include "SDL.h"
#  include "SDL_image.h"
#  include "SDL_ttf.h"
#  include "SDL_mixer.h"
# endif

/*
**	Standart libraries
*/
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*
**	Parts of libmgl
*/
# include "window.h"
# include "ttf.h"
# include "checkbox.h"
# include "color.h"
# include "slider.h"
# include "color_picker.h"
# include "screenshot.h"

# define INVALID_POINTER 0xFF

#endif
