/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhedeon <mhedeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/31 05:08:36 by mhedeon           #+#    #+#             */
/*   Updated: 2019/03/31 05:16:11 by mhedeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libmgl.h"

int					file_exist(const char *filename)
{
	int				fd;

	if ((fd = open(filename, O_RDONLY)) < 0)
		return (0);
	close(fd);
	return (1);
}

static size_t		mgl_strlen(const char *s)
{
	size_t			len;

	len = 0;
	while (*((char *)s))
	{
		len++;
		s++;
	}
	return (len);
}

static char			*mgl_strcpy(char *dst, const char *src)
{
	int				i;

	i = 0;
	while (*(src + i))
	{
		*(dst + i) = *(src + i);
		i++;
	}
	*(dst + i) = '\0';
	return (dst);
}

char				*file_name(void)
{
	char			*filename;
	static Uint8	i1 = 0;
	static Uint8	i2 = 0;
	size_t			name_size;

	name_size = mgl_strlen("screenshot00.png") + 1;
	if ((filename = (char*)malloc(sizeof(char) * name_size)) == NULL)
	{
		error_log("mmry error");
		return (NULL);
	}
	mgl_strcpy(filename, "screenshot00.png");
	while (i1 < 10)
	{
		if (!file_exist(filename))
			return (filename);
		i1 = i1 + (i2 + 1) / 10;
		i2 = (i2 + 1) % 10;
		filename[10] = i1 + '0';
		filename[11] = i2 + '0';
	}
	return (filename);
}
