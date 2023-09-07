/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/07 12:12:46 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*next_line;
	static char	*following;

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	next_line = read_until_new_or_end_line(fd, next_line, following);
	if (!next_line)
		return (NULL);
	return (next_line);
}





int	main(void)
{
	char	*line;
	int		i;
	// int		bytes_leidos;
	int		fd1;
	int		fd2;
	int		fd3;
	// char	buff[1024];
	// static char	*read_content;


	fd1 = open("tests/test_2.txt", O_RDONLY);
	fd2 = open("tests/test_2.txt", O_RDONLY);
	fd3 = open("tests/test_3.txt", O_RDONLY);


	// i = 1;
	// while (i < 10)
	// {
	// 	bytes_leidos = read(fd1, buff, 5);
	// 	printf("\n[%i] - %i - %s\n", i, bytes_leidos, buff);
	// 	i++;
	// }
	// close(fd1);

	
	
	// fd1 = open("tests/test_2.txt", O_RDONLY);
	// read_content = read_until_new_or_end_line(fd1, read_content);

	// close(fd1);



	i = 1;
	while (i < 7)
	{
		line = get_next_line(fd2);
		printf("\nline [%02d]: %s", i, line);
		free(line);

		
		// line = get_next_line(fd1);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// 
		// line = get_next_line(fd3);
		// printf("line [%02d]: %s", i, line);
		// free(line);
		// printf("\nFile descriptor fd1: %d", fd1);
		// printf("\nFile descriptor fd2: %d", fd2);
		// printf("\nFile descriptor fd3: %d", fd3);
		// printf("\n");

		i++;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}