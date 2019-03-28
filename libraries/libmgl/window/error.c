#include "libmgl.h"

int	error_log(const char *message)
{
	if (message == NULL)
		SDL_Log("\x1b[31m%s\x1b[0m\n", SDL_GetError());
	else
		SDL_Log("\x1b[31m%s %s\x1b[0m\n", message, SDL_GetError());
	SDL_ClearError();
	return (0);
}
