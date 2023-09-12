/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/12 12:37:41 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *buff, int rd_bytes, char *ptrToNext)
{
	int	i;
	int	f;
	int	following_lenth;

	// if (*following != NULL)
   	// 	free(*following);
	// *following = malloc(4 * sizeof(char));
	// (*following)[0] = 'a';
	// (*following)[1] = 'b';
	// (*following)[2] = 'c';
	// (*following)[3] = '\0';



	i = 0;
	f = 0;
	while (i < rd_bytes)
	{
		if (buff[i] == '\0')
			return (1);
		if (buff[i] == '\n')
		{
			i++;
			following_lenth = rd_bytes - i;
			if (following_lenth > 1)
			{
				// printf("\n*****Sí que hay Following!!!!");
				// printf("\n*****following_lenth: %i", following_lenth);
				if (ptrToNext != NULL)
					free(ptrToNext);
				ptrToNext = malloc(following_lenth * sizeof(char));
				if (!ptrToNext)
					return (-1);
				while (i < rd_bytes)
				{
					ptrToNext[f] = buff[i];
					i++;
					f++;
				}
				ptrToNext[following_lenth] = '\0';

			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	*read_until_new_or_end_line(int fd, char *ptrToLine, char *ptrToNext)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;
	int		i;

	if (ptrToNext != NULL && ft_strlen(ptrToNext) > 0)
	{
		i = 0;
		ptrToLine = malloc((ft_strlen(ptrToNext) + 1) * sizeof(char));
		while (i < ft_strlen(ptrToNext) + 1)
		{
			ptrToLine[i] = ptrToNext[i];
			i++;
		}
		ptrToLine[i] = '\0';
		// printf("\n AÑÑÑÑÑADIDO FOLLOWING-----> %s", ptrToLine);
		free(ptrToNext);
		ptrToNext = NULL;
	}
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
		printf("\n--------->buff: %s", buff);
		printf("\n--------->ptrToLine: %s", ptrToLine);
		printf("\n--------->");
		new_or_end_line = find_new_or_end_line(buff, rd_bytes, ptrToNext);
		if (new_or_end_line == -1)
			return (NULL);
		ptrToLine = ft_read_join(ptrToLine, buff);
	}
	return (free(buff), ptrToLine);
}

char	*ft_read_join(char *ptrToLine, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!ptrToLine)
	{
		ptrToLine = (char *)malloc(1 * sizeof(char));
		if (!ptrToLine)
			return (NULL);
		ptrToLine[0] = '\0';
	}

	str = malloc(sizeof(char) * (ft_strlen(ptrToLine) + ft_strlen(buff) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (ptrToLine[i] != '\0')
	{
		str[i] = ptrToLine[i];
		i++;
	}
	while (j < ft_strlen(buff) && buff[j] != '\n' && buff[j] != '\0')
	{
		str[i] = buff[j];
		i++;
		j++;
	}
	if (buff[j] == '\n')
		str[i++] = buff[j];
	str[i] = '\0';
	free(ptrToLine);
	return (str);
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
