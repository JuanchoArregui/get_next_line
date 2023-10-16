/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/16 17:29:35 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_n_or_0(char **buff, int rd_bytes, char **ptr_nxt, char **ptr_ln)
{
	char	*str;
	int		brk_len;
	int		find;

	find = 0;
	str = malloc(sizeof(char) * (ft_strlen(*ptr_ln) + rd_bytes + 1));
	if (str == NULL)
		return (-1);
	str[0] = 0;
	if (*ptr_ln != NULL && ft_strlen(*ptr_ln) > 0)
		ft_ptr_cpy_ptr(ptr_ln, 0, ft_strlen(*ptr_ln), &str);
	brk_len = ft_strlen_n(rd_bytes, *buff);
	ft_ptr_cpy_ptr(buff, 0, brk_len, &str);
	if (brk_len > 0 && brk_len < rd_bytes)
	{
		printf("\nrd_bytes: %d", rd_bytes);
		printf("\nbrk_len: %d", brk_len);
		
		
		ft_free_ptr_ptr(ptr_nxt);
		*ptr_nxt = malloc((rd_bytes - brk_len + 1) * sizeof(char));
		if (!*ptr_nxt)
			return (-1);
		ptr_nxt[0] = 0;
		ft_ptr_cpy_ptr(buff, brk_len, rd_bytes, ptr_nxt);
		find = 1;
	}
	*ptr_ln = str;
	return (find);
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
		// check = 1;
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

	printf("\n******************************************");
	printf("\n******************************************");

	ptr_ln = NULL;
	if (ptr_nxt != NULL)
	{
		printf("\nExiste PTR_NEXT");
		nxt_len = ft_strlen(ptr_nxt);
		brk_len = ft_strlen_n(nxt_len, ptr_nxt);
		check = check_ptr_nxt(&ptr_ln, &ptr_nxt, nxt_len, brk_len);
		printf("\ncheck: %d", check);
		printf("\ncheck ptr_ln: %s", ptr_ln);

		if (check == -1)
			return (NULL);
		if (check)
		{
			printf("\ndentro de check - PTR_NEXT: \"%s\"", ptr_nxt);
			return (ptr_ln);
		}
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	printf("\nNO Existe PTR_NEXT y vamos a read_until_n_or_0");
	ptr_ln = read_until_n_or_0(fd, &ptr_ln, &ptr_nxt);
	if (ptr_ln == NULL)
		return (NULL);

	printf("\nPTR_NEXT: \"%s\"", ptr_nxt);
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