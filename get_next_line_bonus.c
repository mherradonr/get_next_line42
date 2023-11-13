/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marherra <marherra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 14:38:26 by marherra          #+#    #+#             */
/*   Updated: 2023/10/31 11:41:32 by marherra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_first_line(char *str)
{
	int		len;
	int		j;
	char	*memory;

	j = 0;
	if (!str || !str[j])
		return (NULL);
	len = 0;
	while (str[len] != '\0' && str[len] != '\n')
		len++;
	memory = malloc((sizeof(char) * len) + 2);
	while (len >= j)
	{
		memory[j] = str[j];
		j++;
	}
	memory[j] = '\0';
	return (memory);
}

char	*delete_first_line(char *str)
{
	char	*memory;
	int		i;
	int		j;

	if (!str[0])
		return (free(str), str = NULL, NULL);
	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	memory = malloc(sizeof(char) * ft_strlen(str) - i + 1);
	if (!memory)
		return (NULL);
	if (str[i] == '\n')
		i++;
	j = 0;
	while (str[i] != '\0')
		memory[j++] = str[i++];
	memory[j] = '\0';
	free (str);
	return (memory);
}

char	*get_next_line(int fd)
{
	char		*str;
	int			read_result;
	static char	*join[OPEN_MAX];
	char		*line;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, 0, 0) < 0)
	{
		if (join[fd])
			free(join[fd]);
		return (join[fd] = NULL, NULL);
	}
	read_result = 1;
	while (read_result && !ft_strchr(join[fd], '\n'))
	{
		str = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!str)
			return (NULL);
		read_result = read(fd, str, BUFFER_SIZE);
		if (read_result == -1)
			return (free(str), str = NULL, NULL);
		str[read_result] = '\0';
		join[fd] = ft_strjoin(join[fd], str);
	}
	line = get_first_line(join[fd]);
	return (join[fd] = delete_first_line(join[fd]), line);
}
