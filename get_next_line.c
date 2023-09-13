/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/14 00:20:39 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*ptr_line;
	static char	*ptr_next;
	int			i;
	int			check;

	ptr_line = NULL;
	if (ptr_next != NULL)
	{
		printf("\n\n\n------------------------------->loooop primario");
		printf("\n ptr_next LENGTH-----> %lu", ft_strlen(ptr_next));

		check = check_ptr_next(&ptr_line, &ptr_next);
		printf("\n resultado de check_ptr_next. CHECK = %i", check);
		if (check == -1)
			return (NULL);
	}
	
	if (ptr_next != NULL ){
		printf("\n Queda NEXT y en teoría ptr_line debe tener algo");
		return (ptr_line);
	}

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ptr_line = read_until_new_or_end_line(fd, &ptr_line, &ptr_next);
	if (!ptr_line)
		return (NULL);
	return (ptr_line);
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
		printf("\n\n\n\n\nLOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOP");
		line = get_next_line(fd2);


		printf("\nline [%02d]: %s", i, line);
		printf("\nline length[%02d]: %lu\n", i, ft_strlen(line));
		if(line != NULL && line[0]== 0)
		{
			printf("\nES UN JODIDO CERO. HEMOS TERMINADO DE LEER");
			break;
		}
		free_ptr_ptr(&line);

		
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