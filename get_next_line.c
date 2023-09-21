/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/21 16:43:40 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_n_or_0(char *buff, int rd_bytes, char **ptr_nxt, char **ptr_ln)
{
	char	*str;
	int		s;
	int		n;
	int		b;
	int		following_lenth;

	s = 0;
	str = malloc(sizeof(char) * (ft_strlen(*ptr_ln) + rd_bytes + 1));
	if (str == NULL)
		return (-1);
	if (*ptr_ln != NULL && ft_strlen(*ptr_ln) > 0)
	{
		while ((*ptr_ln)[s] != '\0')
		{
			str[s] = (*ptr_ln)[s];
			s++;
		}
		ft_free_ptr_ptr(ptr_ln);
	}
	b = 0;
	while (b < rd_bytes)
	{
		if (buff[b] == '\0')
		{
			str[s] = buff[b];
			*ptr_ln = str;
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
				ft_free_ptr_ptr(ptr_nxt);
				*ptr_nxt = malloc((following_lenth + 1) * sizeof(char));
				if (!*ptr_nxt)
					return (-1);
				n = 0;
				while (n < following_lenth)
				{
					(*ptr_nxt)[n] = buff[b];
					n++;
					b++;
				}
				(*ptr_nxt)[n] = '\0';
			}
			*ptr_ln = str;
			return (1);
		}
		else
		{
			str[s] = buff[b];
			s++;
			b++;
		}
	}
	str[s] = '\0';
	*ptr_ln = str;
	return (0);
}

int	check_ptr_nxt(char **ptr_ln, char **ptr_nxt, int nxt_len, int brk_len)
{
	int		ok;
	int		check;

	ok = 0;
	check = 0;
	if (brk_len > 0)
	{
		ok += ft_ptr_cpy_ptr(ptr_nxt, 0, brk_len, ptr_ln);
		check = 1;
		if (nxt_len - brk_len > 0)
			ok += ft_ptr_cpy_ptr(ptr_nxt, brk_len, nxt_len, ptr_nxt);
		else
			ft_free_ptr_ptr(ptr_nxt);
	}
	else if (nxt_len > 0)
	{
		ok += ft_ptr_cpy_ptr(ptr_nxt, 0, nxt_len, ptr_ln);
		ft_free_ptr_ptr(ptr_nxt);
	}
	if (ok < 0)
		return (-1);
	return (check);
}

char	*get_next_line(int fd)
{
	char		*ptr_ln;
	static char	*ptr_nxt;
	int			check;
	int			nxt_len;
	int			brk_len;

	ptr_ln = NULL;
	if (ptr_nxt != NULL)
	{
		nxt_len = ft_strlen(ptr_nxt);
		brk_len = ft_strlen_line_break(nxt_len, ptr_nxt);
		check = check_ptr_nxt(&ptr_ln, &ptr_nxt, nxt_len, brk_len);
		if (check == -1)
			return (NULL);
		if (check)
			return (ptr_ln);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ptr_ln = read_until_n_or_0(fd, &ptr_ln, &ptr_nxt);
	if (ptr_ln == NULL)
		return (NULL);
	return (ptr_ln);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int		fd5;
	int fd_to_open;


	fd1 = open("tests/test_1.txt", O_RDONLY);
	fd2 = open("tests/test_2.txt", O_RDONLY);
	fd3 = open("tests/test_3.txt", O_RDONLY);
	fd4 = open("tests/test_4.txt", O_RDONLY);
	fd5 = open("tests/test_5.txt", O_RDONLY);

	fd_to_open = fd2;

	i = 1;
	printf("\n\n\n\n\nEMPEZAMOS EL BUCLE DE LECTURA");
	line = get_next_line(fd_to_open);
	while (line != NULL)
	{
		printf("\nline [%02d] - length (%d): \"%s\"\n\n", i, ft_strlen(line), line);
		i++;
		ft_free_ptr_ptr(&line);
		line = get_next_line(fd_to_open);
	}
	printf("\nTERMINAD LECTURA!!");
	
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	close(fd5);
	return (0);
}