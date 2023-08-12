/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabastid <pabastid@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 13:06:13 by pabastid          #+#    #+#             */
/*   Updated: 2022/12/02 12:53:53 by pabastid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	static char	*storage;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if ((storage && !ft_strchr(storage, '\n')) || !storage)
		storage = filling_static_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	if (!line)
	{
		free(storage);
		return (NULL);
	}
	storage = save_storage(storage);
	return (line);
}

/*int	main(void)
{
	int		fd;
	char	*line;

	fd = open("text.txt", O_RDONLY);

	line = get_next_line(fd);
	printf("%s", line);
	while (line != NULL)
	{
		free (line);
		line = get_next_line(fd);
		printf("%s", line);
	}
}*/
