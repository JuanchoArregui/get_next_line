/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:17:26 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/31 16:06:44 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	split_buff(char **ptr_buff, char **ptr_ln, char **ptr_nxt)
{
	char	*ptr_temp;
	int		check;
	int		buff_len;
	int		buff_nl_len;

	check = 0;
	ptr_temp = NULL;
	buff_len = ft_strlen(*ptr_buff);
	buff_nl_len = ft_strlen_n(*ptr_buff);
	if (buff_nl_len > 0 && buff_len > buff_nl_len)
	{
		check += ft_ptr_cpy_ptr(ptr_buff, buff_nl_len, 0, &ptr_temp);
		(*ptr_buff)[buff_nl_len] = '\0';
	}
	check += ft_ptr_cpy_ptr(ptr_buff, 0, ft_strlen(*ptr_ln), ptr_ln);
	ft_free_ptr_ptr(ptr_buff);
	if (ptr_nxt != NULL)
		ft_free_ptr_ptr(ptr_nxt);
	*ptr_nxt = ptr_temp;
	if (check < 0)
		return (-1);
	if (buff_nl_len > 0)
		return (1);
	return (0);
}

char	*read_until_n_or_0(int fd, char **ptr_ln, char **ptr_nxt)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	rd_bytes = 1;
	new_or_end_line = 0;
	while (!new_or_end_line && rd_bytes > 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		else if (rd_bytes == 0)
			return (free(buff), *ptr_ln);
		buff[rd_bytes] = '\0';
		new_or_end_line = split_buff(&buff, ptr_ln, ptr_nxt);
		if (new_or_end_line < 0)
			return (NULL);
		else if (new_or_end_line == 1)
			return (*ptr_ln);
	}
	return (ft_free_ptr_ptr(ptr_ln), NULL);
}

char	*get_next_line(int fd)
{
	char		*ptr_ln;
	static char	*ptr_nxt[MAX_THREADS];
	int			new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr_ln = NULL;
	if (ptr_nxt[fd] != NULL)
	{
		new_line = split_buff(&ptr_nxt[fd], &ptr_ln, &ptr_nxt[fd]);
		if (new_line < 0)
			return (NULL);
		if (new_line == 1)
			return (ptr_ln);
	}
	ptr_ln = read_until_n_or_0(fd, &ptr_ln, &ptr_nxt[fd]);
	return (ptr_ln);
}

// int	main(void)
// {
// 	char	*line;
// 	int		i;
// 	int		fd1;
// 	int		fd2;
// 	int		fd3;

// 	fd1 = open("tests/test_2.txt", O_RDONLY);
// 	fd2 = open("tests/test_3.txt", O_RDONLY);
// 	fd3 = open("tests/test_4.txt", O_RDONLY);
// 	i = 1;

// 	while (i < 7)
// 	{
// 		line = get_next_line(fd1);
// 		printf("\n\n\nline [NUMBERS - %02d]: \"%s\"", i, line);
// 		ft_free_ptr_ptr(&line);
// 		line = get_next_line(fd2);
// 		printf("\nline [LOREM IPSUM %02d]: \"%s\"", i, line);
// 		ft_free_ptr_ptr(&line);
// 		line = get_next_line(fd3);
// 		printf("\nline [LETTERS - %02d]: \"%s\"", i, line);
// 		ft_free_ptr_ptr(&line);
// 		i++;
// 	}
// 	close(fd1);
// 	close(fd2);
// 	close(fd3);
// 	return (0);
// }
