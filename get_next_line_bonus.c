/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ansulist <ansulist@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/01 18:02:21 by ansulist          #+#    #+#             */
/*   Updated: 2023/02/09 11:13:06 by ansulist         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <limits.h>

char	*ft_strndup(const char *src, int n)
{
	int		i;
	char	*str;

	i = 0;
	str = malloc(sizeof(char) * (n + 1));
	if (str == 0)
		return (0);
	while (i < n)
	{
		str[i] = src[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_reading(int fd, char *text)
{
	char	*buffer;
	int		bytes;

	buffer = (char *)malloc((size_t)BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(text, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[bytes] = '\0';
		text = ft_strjoin(text, buffer);
		if (text == NULL)
		{
			free(buffer);
			return (NULL);
		}
	}
	free(buffer);
	return (text);
}

char	*line_by_line(char *text)
{
	int		i;

	i = 0;
	if (text[i] == '\0')
		return (NULL);
	while (text[i] && text[i] != '\n')
		i++;
	return (ft_strndup(text, i + 1));
}

char	*modified_line(char *str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\0')
	{
		free(str);
		return (NULL);
	}
	temp = ft_strdup(str + i + 1);
	free(str);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*text[OPEN_MAX + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483647)
		return (0);
	text[fd] = ft_reading(fd, text[fd]);
	if (text[fd] == NULL)
		return (NULL);
	line = line_by_line(text[fd]);
	text[fd] = modified_line(text[fd]);
	return (line);
}
