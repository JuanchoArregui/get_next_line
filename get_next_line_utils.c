/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/08/22 22:46:44 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_find_new_or_end_line(char *s, int rd_bytes)
{
	size_t	i;

	if (rd_bytes == 0)
		return (1);
	i = 0;
	while (s[i] != '\n')
	{
		if (s[i] == '\0' && i < rd_bytes)
			return (1);
		i++;
	}
	return (i);
}

char	*ft_read_feeding(int fd, char *read_content)
{
	char	*buff;
	int		rd_bytes;
	size_t	new_or_end_line;
int	i;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	new_or_end_line = 0;
i = 0;

	// while (new_or_end_line == 0 && rd_bytes != 0)
	while (i < 3)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		buff[rd_bytes] = '\0';
		// new_or_end_line = ft_find_new_or_end_line(buff, rd_bytes);

		//
		printf("\nAQUI");
		printf("\nbuff: %s", buff);
		printf("\nd_bytes: %i", rd_bytes);
		// read_content = ft_strjoin(read_content, buff);
		i++;
	}
	free(buff);
	return (read_content);
}