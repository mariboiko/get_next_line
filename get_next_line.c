/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboiko <mboiko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 09:18:13 by mariboiko         #+#    #+#             */
/*   Updated: 2022/12/19 14:27:41 by mboiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdlib.h>

static char	*ft_after(char *line)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	j = ft_strlen(line);
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
	{
		free(line);
		return (NULL);
	}
	temp = malloc(sizeof(char) * (j - i));
	if (!temp)
		return (NULL);
	j = 0;
	i++;
	while (line[i])
		temp[j++] = line[i++];
	temp[j] = '\0';
	free(line);
	if (temp[0] == '\0')
	{
		free(temp);
		temp = NULL;
	}
	return (temp);
}

static char	*ft_before(char *line)
{
	int			i;
	char		*temp;

	i = 0;
	if (!line[i])
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	temp = (char *)malloc(sizeof(char) * (i + 2));
	if (!temp)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		temp[i] = line[i];
		i++;
	}
	if (line[i] == '\n')
	{
		temp[i] = line[i];
		i++;
	}
	temp[i] = '\0';
	return (temp);
}

char	*ft_read(int fd, char *result, char *buffer)
{
	ssize_t	reated;

	reated = 1;
	while (reated > 0)
	{
		reated = read(fd, buffer, BUFFER_SIZE);
		if (reated == -1)
		{
			free(buffer);
			return (NULL);
		}
		buffer[reated] = '\0';
		result = ft_strjoin(result, buffer);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (result);
}

char	*get_next_line(int fd)
{
	static char		*line_save;
	char			*line;
	char			*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line_save = ft_read(fd, line_save, buffer);
	if (!line_save)
		return (NULL);
	line = ft_before(line_save);
	line_save = ft_after(line_save);
	free(buffer);
	return (line);
}
