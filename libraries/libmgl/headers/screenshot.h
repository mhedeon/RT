/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:29:45 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:29:45 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCREENSHOT_H
# define SCREENSHOT_H

# include "libmgl.h"

int		file_exist(const char *filename);
char	*file_name(void);

void	screenshot(SDL_Renderer *ren, SDL_Texture *tex, SDL_Rect *rect);

#endif
