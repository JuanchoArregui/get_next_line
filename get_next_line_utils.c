/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/21 15:29:08 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_until_n_or_0(int fd, char **ptr_ln, char **ptr_nxt)
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
		new_or_end_line = find_n_or_0(buff, rd_bytes, ptr_nxt, ptr_ln);
		if (new_or_end_line == -1)
			return (NULL);
	}
	if (*ptr_ln[0] == 0)
		return (ft_free_ptr_ptr(ptr_ln), NULL);
	return (free(buff), *ptr_ln);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_line_break(int length, char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (i < length && s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1 + i);
		i++;
	}
	return (0);
}

void	ft_free_ptr_ptr(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_ptr_cpy_ptr(char **src, int start, int end, char **dest)
{
	char	*str;
	int		s;
	int		i;

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
	return (0);
}
