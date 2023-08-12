/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:53:26 by pabastid          #+#    #+#             */
/*   Updated: 2022/12/07 12:24:04 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*filling_static_storage(int fd, char *storage)
{
	char	*buffer;
	int		bytes_readed;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_readed = 1;
	while (bytes_readed > 0 && !ft_strchr(buffer, '\n'))
	{
		bytes_readed = read (fd, buffer, BUFFER_SIZE);
		if (bytes_readed > 0)
		{
			buffer [bytes_readed] = '\0';
			storage = ft_strjoin(storage, buffer);
		}
	}
	free(buffer);
	if (bytes_readed == -1)
	{
		free(storage);
		return (NULL);
	}
	return (storage);
}

char	*extract_line(char *storage)
{
	int		len;
	char	*aux;
	char	*line;

	aux = ft_strchr(storage, '\n');
	len = (aux - storage) + 1;
	line = ft_substr(storage, 0, len);
	if (line[0] == '\0')
		return (NULL);
	return (line);
}

char	*save_storage(char *storage)
{
	char	*temp;
	char	*aux;
	int		len;

	aux = ft_strchr(storage, '\n');
	if (!aux)
	{
		free(storage);
		temp = NULL;
		return (NULL);
	}
	else
		len = (aux - storage) + 1;
	if (!storage[len])
	{
		free(storage);
		return (NULL);
	}
	temp = ft_substr(storage, len, ft_strlen(storage) - len);
	free(storage);
	return (temp);
}

char	*get_next_line(int fd)
{
	static char	*storage[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((storage[fd] && !ft_strchr(storage[fd], '\n')) || !storage[fd])
		storage[fd] = filling_static_storage(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = extract_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		return (NULL);
	}
	storage[fd] = save_storage(storage[fd]);
	return (line);
}

int	main(void)
{
	int		fd[3];
	int		i;
	char	*line;

	i = 0;
	fd[0] = open("text.txt", O_RDONLY);
	fd[1] = open("text00.txt", O_RDONLY);
	fd[2] = open("text01.txt", O_RDONLY);
	line = get_next_line(fd[i]);
	printf("\n\n<FIRST TEXT>\n\n");
	printf("%s", line);
	while (i < 3)
	{
		if (i > 0)
			printf("\n\n<NEXT TEXT>\n\n");
		free(line);
			line = get_next_line(fd[i]);
			printf("%s", line);
			while (line != NULL)
			{
				free(line);
				line = get_next_line(fd[i]);
				printf("%s", line);
			}
			i++;
	}

	while (i< 5)
	{
		line = get_next_line(fd[0]);
		printf("%s", line);
		line = get_next_line(fd[1]);
		printf("%s", line);
		line = get_next_ne(fd[2]);
		printf("%s", line);
		i++;
	}
	printf("\n\nOPENMAX == %i\n\n", OPEN_MAX);
}
