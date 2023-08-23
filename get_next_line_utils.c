/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/08/23 20:39:32 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *s, int rd_bytes)
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

char	*read_until_new_or_end_line(int fd, char *read_content)
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
		new_or_end_line = find_new_or_end_line(buff, rd_bytes);


		printf("\nbuff: %s", buff);
		printf("\nd_bytes: %i", rd_bytes);
		printf("\n");
		read_content = ft_strjoin(read_content, buff);
	}
	free(buff);
	return (read_content);
}

char	*ft_strjoin(char *read_content, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!read_content)
	{
		read_content = (char *)malloc(1 * sizeof(char));
		read_content[0] = '\0';
	}
	if (!read_content || !buff)
		return (NULL);
	str = malloc(sizeof(char) * ((ft_strlen(read_content) + ft_strlen(buff)) + 1));
	if (str == NULL)
		return (NULL);
	i = -1;
	j = 0;
	if (read_content)
		while (read_content[++i] != '\0')
			str[i] = read_content[i];
	while (buff[j] != '\0')
		str[i++] = buff[j++];
	str[ft_strlen(read_content) + ft_strlen(buff)] = '\0';
	free(read_content);
	return (str);
}
