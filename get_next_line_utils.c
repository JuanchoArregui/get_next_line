/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/14 22:45:44 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


int	find_new_or_end_line(char *buff, int rd_bytes, char **ptr_next, char **ptr_line)
{
	char	*str;
	int		s;
	int		n;
	int		b;
	int		following_lenth;

	s = 0;
	str = malloc(sizeof(char) * (ft_strlen(*ptr_line) + rd_bytes + 1));
	printf("\nrd_bytes: %i", rd_bytes);
	printf("\nLEngth de str: %li", ft_strlen(*ptr_line) + rd_bytes + 1);
	if (str == NULL)
		return (-1);
	//1º miramos si había ya algo en ptr_line
	if (*ptr_line != NULL && ft_strlen(*ptr_line) > 0) {


		while ((*ptr_line)[s] != '\0') 
		{
			printf("\n-S: %i", s);
			str[s] = (*ptr_line)[s];
			s++;
		}
		printf("\n");

		ft_free_ptr_ptr(ptr_line);
	} else {
		printf("\nno hay nada EN PTR_LINE: %p", *ptr_line);
	}
	//2º miramos el buffer
	b = 0;
	while (b < rd_bytes)
	{
		if (buff[b] == '\0')
		{
			str[s] = buff[b];
			*ptr_line = str;
			return (1);
		}
		else if (buff[b] == '\n')
		{
			str[s] = buff[b];
			s++;
			b++;
			str[s] = '\0';
			following_lenth = rd_bytes - b;
			if (following_lenth > 0)
			{
				ft_free_ptr_ptr(ptr_next);
				*ptr_next = malloc((following_lenth + 1) * sizeof(char));
				if (!*ptr_next)
					return (-1);
				n = 0;
				while (n < following_lenth)
				{
					(*ptr_next)[n] = buff[b];
					n++;
					b++;
				}
				(*ptr_next)[n] = '\0';
			}
			*ptr_line = str;
			return (1);
		} else {
			str[s] = buff[b];
			s++;
			b++;
		}
	}
	str[s] = '\0';
	*ptr_line = str;
	return (0);
}

char	*read_until_new_or_end_line(int fd, char **ptr_line, char **ptr_next)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;
	
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
		printf("\n\n\n------------------------------->loooop secundario");
		printf("\n--------->buff: %s", buff);
		printf("\n--------->");


		new_or_end_line = find_new_or_end_line(buff, rd_bytes, ptr_next, ptr_line);
		if (new_or_end_line == -1)
			return (NULL);
		// *ptr_line = ft_read_join(ptr_line, buff);
	}
	return (free(buff), *ptr_line);
}

int	check_ptr_next(char **ptr_line, char **ptr_next)
{
	size_t	next_length;
	size_t	next_line_length;
	size_t	remaining;
	int		ok;

	next_length = ft_strlen(*ptr_next);
	next_line_length = ft_strlen_line(*ptr_next);
	if (next_line_length > 0)
	{
		ok = ft_ptr_cpy_ptr(ptr_next, 0, next_line_length, ptr_line);
		if (ok == -1)
			return (-1);
	}
	remaining = next_length - next_line_length;
	if (remaining > 0)
	{
		ok = ft_ptr_cpy_ptr(ptr_next, next_line_length, next_length, ptr_next);
		if (ok == -1)
			return (-1);
	}
	else 
		ft_free_ptr_ptr(ptr_next);
	return (1);
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

size_t	ft_strlen_line(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	return (i);
}

void	ft_free_ptr_ptr(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_ptr_cpy_ptr(char **src, size_t start, size_t end, char **dest)
{
	char	*str;
	size_t	s;
	size_t	i;

	str = malloc((end + 1) * sizeof(char));
	if (str == NULL)
		return (-1);
	s = 0;
	i = start;
	while (i < end)
	{
		str[s] = (*src)[i];
		i++;
		s++;
	}
	str[s] = '\0';
	if (src == dest)
		ft_free_ptr_ptr(src);
	*dest = str;
	return (1);
}
