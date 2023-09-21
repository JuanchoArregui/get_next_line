/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/21 13:39:47 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_ptr_next(char **ptr_line, char **ptr_next)
{
	size_t	next_length;
	size_t	next_line_length;
	size_t	remaining;
	int		ok;
	int		check;

	check = 0;
	next_length = ft_strlen(*ptr_next);
	next_line_length = ft_strlen_line(*ptr_next);

		printf("\n----->next_length: %lu", next_length);
		printf("\n----->next_line_length: %lu", next_line_length);

	if (next_line_length > 0)
	{
		ok = ft_ptr_cpy_ptr(ptr_next, 0, next_line_length, ptr_line);
		if (ok == -1)
			return (-1);
		check = 1;
	}
	remaining = next_length - next_line_length;
	if (remaining > 0)
	{
		printf("\n----->hay remaining");
		ok = ft_ptr_cpy_ptr(ptr_next, next_line_length, next_length, ptr_next);
		if (ok == -1)
			return (-1);
	}
	else
		ft_free_ptr_ptr(ptr_next);
	return (check);
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
		printf("\n----->ptr_next AL ENTRAR = \"%s\"", ptr_next);


		check = check_ptr_next(&ptr_line, &ptr_next);
		printf("\n----->resultado de check_ptr_next. CHECK = %i", check);
		if (check == -1)
			return (NULL);

		if (ptr_line != NULL )
			printf("\n----->ptr_line AL SALIR = \"%s\"", ptr_line);
		if (ptr_next != NULL )
			printf("\n----->ptr_next  AL SALIR = \"%s\"", ptr_next);

		// if (ptr_next != NULL && ptr_line != NULL )
		if (check)
			return (ptr_line);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	ptr_line = read_until_n_or_0(fd, &ptr_line, &ptr_next);
	if (ptr_line == NULL)
		return (NULL);
	return (ptr_line);
}

int	main(void)
{
	char	*line;
	int		i;
	int		fd1;
	int		fd2;
	int		fd3;
	int		fd4;
	int fd_to_open;


	fd1 = open("tests/test_1.txt", O_RDONLY);
	fd2 = open("tests/test_2.txt", O_RDONLY);
	fd3 = open("tests/test_3.txt", O_RDONLY);
	fd4 = open("tests/test_4.txt", O_RDONLY);

	fd_to_open = fd2;

	i = 1;
	printf("\n\n\n\n\nEMPEZAMOS EL BUCLE DE LECTURA");
	line = get_next_line(fd_to_open);
	while (line != NULL)
	{
		printf("\nline [%02d] - length (%lu): \"%s\"\n\n", i, ft_strlen(line), line);
		i++;
		ft_free_ptr_ptr(&line);
		line = get_next_line(fd_to_open);
	}
	printf("\nHEMOS TERMINADO DE LEER!! (o ha habido un error)");
	
	close(fd1);
	close(fd2);
	close(fd3);
	close(fd4);
	return (0);
}