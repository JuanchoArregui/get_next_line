/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/07 18:52:57 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *s, int rd_bytes, char **following)
{
	int	i;

	if (*following != NULL)
   		free(*following);
	*following = malloc(4 * sizeof(char));
	(*following)[0] = 'a';
	(*following)[1] = 'b';
	(*following)[2] = 'c';
	(*following)[3] = '\0';



	i = 0;
	while (i < rd_bytes)
	{
		if (s[i] == '\0' || s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_until_new_or_end_line(int fd, char *next_line, char **following)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	// (*following)[0] = 'A';

	rd_bytes = 1;
	new_or_end_line = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	while (!new_or_end_line && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		buff[rd_bytes] = '\0';
		// printf("\n--------->buff: %s", buff);
		// printf("\n--------->next_line: %s", next_line);
		// printf("\n--------->");

		new_or_end_line = find_new_or_end_line(buff, rd_bytes, following);
		if (new_or_end_line == -1)
			return (NULL);
		next_line = ft_read_join(next_line, buff);
	}
	return (free(buff), next_line);
}

char	*ft_read_join(char *next_line, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!next_line)
	{
		next_line = (char *)malloc(1 * sizeof(char));
		if (!next_line)
			return (NULL);
		next_line[0] = '\0';
	}
	str = malloc(sizeof(char) * (ft_strlen(next_line) + ft_strlen(buff) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (next_line[i] != '\0')
	{
		str[i] = next_line[i];
		i++;
	}
	free(next_line);
	while (j < ft_strlen(buff))
		str[i++] = buff[j++];
	return (str[i] = '\0', str);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
