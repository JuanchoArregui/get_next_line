/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/18 11:19:22 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	split_buff(char **ptr_buff, char **ptr_ln, char **ptr_nxt)
{
	char	*ptr_temp;
	int		check;
	int		brk_len;

	if (!ptr_buff)
		return (-1);
	check = 0;
	ptr_temp = NULL;
	brk_len = ft_strlen_n(*ptr_buff);
	if (brk_len > 0)
	{
		check += ft_ptr_cpy_ptr(ptr_buff, brk_len, 0, &ptr_temp);
		(*ptr_buff)[brk_len] = '\0';
	}
	check += ft_ptr_cpy_ptr(ptr_buff, 0, ft_strlen(*ptr_ln), ptr_ln);
	ft_free_ptr_ptr(ptr_buff);
	if (ptr_nxt != NULL)
		ft_free_ptr_ptr(ptr_nxt);
	*ptr_nxt = ptr_temp;
	if (check < 0)
		return (-1);
	if (brk_len > 0)
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
	static char	*ptr_nxt;
	int			new_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ptr_ln = NULL;
	if (ptr_nxt != NULL)
	{
		new_line = split_buff(&ptr_nxt, &ptr_ln, &ptr_nxt);
		if (new_line < 0)
			return (NULL);
		if (new_line == 1)
			return (ptr_ln);
	}
	ptr_ln = read_until_n_or_0(fd, &ptr_ln, &ptr_nxt);
	return (ptr_ln);
}

// int	main(void)
// {
// 	char	*line;
// 	int		t;
// 	int		i;
// 	char	file_name[17];
// 	int		fd;

// 	t = 0;
// 	while (t < 7)
// 	{
// 		i = 1;
// 		sprintf(file_name, "%s%d%s", "tests/test_", t, ".txt");
// 		fd = open(file_name, O_RDONLY);
// 		printf("\n\n\n\n\nARCHIVO - %d - %s", t++, file_name);
// 		line = get_next_line(fd);
// 		while (line != NULL)
// 		{
// 			printf("\nline [%02d]: \"%s\"", i, line);
// 			i++;
// 			ft_free_ptr_ptr(&line);
// 			line = get_next_line(fd);
// 		}
// 		ft_free_ptr_ptr(&line);
// 		close(fd);
// 	}
// 	return (0);
// }
