/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 06:36:09 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 06:36:10 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXT_H
# define TEXT_H

# include "rt.h"

# define T_LIST (SDL_Rect) { 25, 250, 250, 50 }
# define LIST_O (SDL_Rect) { 30, 255, 240, 40 }

# define T_R (SDL_Rect) { 1140, 465, 100, 30 }
# define T_G (SDL_Rect) { 1140, 505, 100, 30 }
# define T_B (SDL_Rect) { 1140, 545, 100, 30 }

# define T_H (SDL_Rect) { 1270, 465, 100, 30 }
# define T_S (SDL_Rect) { 1270, 505, 100, 30 }
# define T_V (SDL_Rect) { 1270, 545, 100, 30 }

# define T_OBJ (SDL_Rect) { 130, 20, 130, 30 }

# define T_X (SDL_Rect) { 50, 60, 100, 30 }
# define T_Y (SDL_Rect) { 50, 100, 100, 30 }
# define T_Z (SDL_Rect) { 50, 140, 100, 30 }

# define T_XA (SDL_Rect) { 250, 60, 100, 30 }
# define T_YA (SDL_Rect) { 250, 100, 100, 30 }
# define T_ZA (SDL_Rect) { 250, 140, 100, 30 }

# define T_SPEC (SDL_Rect) { 550, 60, 300, 30}
# define T_REFL (SDL_Rect) { 550, 100, 300, 30}

# define T_CAM (SDL_Rect) { 1135, 20, 130, 30 }

# define C_X (SDL_Rect) { 1050, 60, 100, 30 }
# define C_Y (SDL_Rect) { 1050, 100, 100, 30 }
# define C_Z (SDL_Rect) { 1050, 140, 100, 30 }

# define C_XA (SDL_Rect) { 1250, 60, 100, 30 }
# define C_YA (SDL_Rect) { 1250, 100, 100, 30 }
# define C_ZA (SDL_Rect) { 1250, 140, 100, 30 }

# define T_SEPIA (SDL_Rect) { 1170, 615, 50, 20 }

# define T_RENDER (SDL_Rect) { 1200, 950, 100, 30 }
# define T_SHOT (SDL_Rect) { 1175, 900, 150, 30 }

#endif
