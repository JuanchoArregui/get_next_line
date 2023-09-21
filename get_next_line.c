/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/21 11:25:40 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_ptr_next(char **ptr_line, char **ptr_next)
{
	size_t	next_length;
	size_t	next_line_length;
	size_t	remaining;
	int		ok;

	next_length = ft_strlen(*ptr_next);
	next_line_length = ft_strlen_line(*ptr_next);

		printf("\n----->next_length: %lu", next_length);
		printf("\n----->next_line_length: %lu", next_line_length);

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

char	*get_next_line(int fd)
{
	char		*ptr_line;
	static char	*ptr_next;
	int			check;

	ptr_line = NULL;
	if (ptr_next != NULL)
	{
		printf("\n----->loooop primario");
		printf("\n----->Queda NEXT y en teoría ptr_line debe tener algo");
		printf("\n----->ptr_next LENGTH: %lu", ft_strlen(ptr_next));

		check = check_ptr_next(&ptr_line, &ptr_next);
		printf("\n----->resultado de check_ptr_next. CHECK = %i", check);
		if (check == -1)
			return (NULL);

		if (ptr_line != NULL )
			printf("\n----->ptr_line = \"%s\"", ptr_line);
		if (ptr_next != NULL )
			printf("\n----->ptr_next = \"%s\"", ptr_next);

		if (ptr_next != NULL && ptr_line != NULL )
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
	printf("\n\n\n\n\nEMPEZAMOS EL BUCLE DE 7 LLAMADAS A GET NEXT LINE");
	line = get_next_line(fd2);
	printf("\nline [%02d] - length (%lu): \"%s\"", i, ft_strlen(line), line);
	while (line != NULL && line[0] != 0)
	{
		i++;
		ft_free_ptr_ptr(&line);
		line = get_next_line(fd2);
		printf("\nline [%02d] - length (%lu): \"%s\"", i, ft_strlen(line), line);
	}
	if (line != NULL && line[0] == 0)
	{
		printf("\nES UN JODIDO CERO. HEMOS TERMINADO DE LEER");
		ft_free_ptr_ptr(&line);
	}
	else
	{
		printf("\nERROR NO DEBERIAMOS ESTAR AQUI");

	}


	// i = 1;
	// while (i < 7)
	// {
	// 	printf("\n\n************************ BUCLE[%02d]", i);

	// 	printf("\nline [%02d] - length (%lu): \"%s\"", i, ft_strlen(line), line);
	// 	if (line != NULL && line[0] == 0)
	// 	{
	// 		printf("\nES UN JODIDO CERO. HEMOS TERMINADO DE LEER");
	// 		ft_free_ptr_ptr(&line);
	// 		break ;
	// 	}
	// 	ft_free_ptr_ptr(&line);
	// 	i++;
	// }



	close(fd1);
	close(fd2);
	close(fd3);
	return (0);
}