/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/12 14:28:07 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *buff, int rd_bytes, char **ptr_next)
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
				if (*ptr_next != NULL)
					free(*ptr_next);
				*ptr_next = malloc(following_lenth * sizeof(char));
				if (!*ptr_next)
					return (-1);
				while (i < rd_bytes)
				{
					(*ptr_next)[f] = buff[i];
					i++;
					f++;
				}
				(*ptr_next)[following_lenth] = '\0';
				printf("\n*****Sí que hay Following!!!!");
				printf("\n*****following_lenth: %i", following_lenth);
				printf("\n*****following_lenth STRING: %s", *ptr_next);

			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	*read_until_new_or_end_line(int fd, char **ptr_line, char **ptr_next)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;
	int		i;

	// if (ptr_next != NULL && ft_strlen(ptr_next) > 0)
	// {
	// 	i = 0;
	// 	ptr_line = malloc((ft_strlen(ptr_next) + 1) * sizeof(char));
	// 	while (i < ft_strlen(ptr_next) + 1)
	// 	{
	// 		ptr_line[i] = ptr_next[i];
	// 		i++;
	// 	}
	// 	ptr_line[i] = '\0';
	// 	printf("\n AÑÑÑÑÑADIDO FOLLOWING-----> %s", ptr_line);
	// 	free(ptr_next);
	// 	ptr_next = NULL;
	// }
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
		// printf("\n--------->ptr_line: %s", ptr_line);
		// printf("\n--------->");
		new_or_end_line = find_new_or_end_line(buff, rd_bytes, ptr_next);
		if (new_or_end_line == -1)
			return (NULL);
		*ptr_line = ft_read_join(ptr_line, buff);
	}
	return (free(buff), *ptr_line);
}

char	*ft_read_join(char **ptr_line, char *buff)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!*ptr_line)
	{
		*ptr_line = (char *)malloc(1 * sizeof(char));
		if (!*ptr_line)
			return (NULL);
		(*ptr_line)[0] = '\0';
	}

	str = malloc(sizeof(char) * (ft_strlen(*ptr_line) + ft_strlen(buff) + 1));
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while ((*ptr_line)[i] != '\0')
	{
		str[i] = (*ptr_line)[i];
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
	free(ptr_line);
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
