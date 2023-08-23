/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/08/23 20:20:25 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_find_new_or_end_line(char *s, int rd_bytes)
{
	int	i;

	i = 0;
	while (i < rd_bytes)
	{
		if (s[i] == '\0' || s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read_feeding(int fd, char *read_content)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	new_or_end_line = 0;
	while (!new_or_end_line && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		buff[rd_bytes] = '\0';
		new_or_end_line = ft_find_new_or_end_line(buff, rd_bytes);


		printf("\nbuff: %s", buff);
		printf("\nd_bytes: %i", rd_bytes);
		printf("\n");
		// read_content = ft_strjoin(read_content, buff);
	}
	free(buff);
	return (read_content);
}