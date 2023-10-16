/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/16 17:59:14 by jarregui         ###   ########.fr       */
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
	buff[0] = 0;
	while (!new_or_end_line && rd_bytes > 0)
	{
		printf("\ndentro del while read_until_n_or_0");

		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		buff[rd_bytes] = '\0';
		new_or_end_line = find_n_or_0(&buff, rd_bytes, ptr_nxt, ptr_ln);

		printf("\nnew_or_end_line: %d", new_or_end_line);
		printf("\nptr_nxt: %s", *ptr_nxt);
		printf("\nptr_ln: %s", *ptr_ln);


		if (new_or_end_line == -1)
			return (NULL);
	}
	if (*ptr_ln[0] == 0)
	{
			printf("\ndentro del while NULL b");

		return (ft_free_ptr_ptr(ptr_ln), NULL);
	}
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

int	ft_strlen_n(int length, char *s)
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

int	ft_ptr_cpy_ptr(char **src, int s_ini, int s_end, char **dest)
{
	char	*str;
	int		d_old;
	int		d;

	d = 0;
	if (dest == NULL)
		d_old = 0;
	else
		d_old = ft_strlen(*dest);


	printf("\nft_ptr_cpy_ptr d_old: %d", d_old);
	printf("\nft_ptr_cpy_ptr d_old: %d", d);
	if (d < d_old)
		printf("\n-------->SIIIIIII se cumple que d < d_old");
	else
		printf("\n-------->NO se cumple que d < d_old");


	str = malloc((d_old + (s_end - s_ini) + 1) * sizeof(char));
	if (str == NULL)
		return (-1);
	str[0] = 0;
	while (d < d_old)
	{
		printf("\nft_ptr_cpy_ptr había algo en dest. d: %d - d_old: %d - char: \"%c\"", d, d_old, (*dest)[d]);
		str[d] = (*dest)[d];
		d++;
	}
	while (s_ini < s_end)
	{
		str[d] = (*src)[s_ini];
		s_ini++;
		d++;
	}
	str[d] = '\0';
	if (src == dest)
		ft_free_ptr_ptr(src);
	*dest = str;
	return (0);
}
