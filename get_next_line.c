/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/08/22 15:03:33 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>



#include <stdio.h>
#include <fcntl.h>

// char	*ft_read_to_left_str(int fd, char *left_str)
// {
// 	char	*buff;
// 	int		rd_bytes;

// 	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	if (!buff)
// 		return (NULL);
// 	rd_bytes = 1;
// 	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
// 	{
// 		rd_bytes = read(fd, buff, BUFFER_SIZE);
// 		if (rd_bytes == -1)
// 		{
// 			free(buff);
// 			return (NULL);
// 		}
// 		buff[rd_bytes] = '\0';
// 		left_str = ft_strjoin(left_str, buff);
// 	}
// 	free(buff);
// 	return (left_str);
// }

// char	*get_next_line(int fd)
// {
// 	char		*line;
// 	static char	*left_str;

// 	if (fd < 0 || BUFFER_SIZE <= 0)
// 		return (0);
// 	left_str = ft_read_to_left_str(fd, left_str);
// 	if (!left_str)
// 		return (NULL);
// 	line = ft_get_line(left_str);
// 	left_str = ft_new_left_str(left_str);
// 	return (line);
// }

int	main(void)
{
	// char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	i = 1;
	while (i < 7)
	{
		fd1 = open("tests/test_1.txt", O_RDONLY);
		fd2 = open("tests/test_2.txt", O_RDONLY);
		fd3 = open("tests/test_3.txt", O_RDONLY);
		// line = get_next_line(fd1);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd2);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		i++;
		printf("\nFile descriptor fd1: %d", fd1);
		printf("\nFile descriptor fd2: %d", fd2);
		printf("\nFile descriptor fd3: %d", fd3);
		printf("\n");

		close(fd1);
		close(fd2);
		close(fd3);
	}
	return (0);
}