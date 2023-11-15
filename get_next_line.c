/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:02:50 by jarregui          #+#    #+#             */
/*   Updated: 2023/11/15 11:04:39 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"



/*
NOTA: están sin subr a git los cambios, así que en staging se puede ver la diferencia.
Básicamente he modifiicado la función split (para que solo use 2 variables buff y ln) en vez de una adicional temporal como hacía antes
creo que es más limpio y más sencillo pero me da un error al acabar.
Verificar y seguir viendo gestión de errores a ver si paco deja de darme leak
*/


int	split_buff(char **ptr_buff, char **ptr_ln)
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
	*ptr_buff = ptr_temp;
	if (check < 0)
		return (-1);
	if (buff_nl_len > 0)
		return (1);
	return (0);
}

char	*read_until_n_or_0(int fd, char **ptr_buff, char **ptr_ln)
{
	int		rd_bytes;
	int		new_or_end_line;

	rd_bytes = 1;
	new_or_end_line = 0;

	printf("\n ////////////////");
	printf("\n ENTRANDO EN READ");
	printf("\n ////////////////");

	
	// printf("\n recibido en READ UNTIL --> ptr_ln: %p \"%s\"", ptr_buff, *ptr_buff);
	
	if (*ptr_buff != NULL)
	{
		// printf("\nptr_buff: \"%s\"", *ptr_buff);
		printf("\n******************************************");
		printf("\nptr_buff no es NULL. esto no debería pasar");
		printf("\n******************************************");

	}




	while (!new_or_end_line && rd_bytes > 0)
	{
		*ptr_buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!(*ptr_buff))
			return (NULL);
		rd_bytes = read(fd, *ptr_buff, BUFFER_SIZE);
	printf("\n      rd_bytes: \"%d\"", rd_bytes);

		if (rd_bytes == -1)
			return (free(*ptr_buff), NULL);
		else if (rd_bytes == 0)
		{
			printf("\n      rd_bytes: ESTOY EN ZERO BYTES");
			// printf("\n      rd_bytes: \"%s\"", *ptr_buff);

			return (free(*ptr_buff), *ptr_ln);
			
		}
		(*ptr_buff)[rd_bytes] = '\0';
	printf("\n READ --> ptr_buff: \"%s\"", *ptr_buff);
	
		
		new_or_end_line = split_buff(ptr_buff, ptr_ln);
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
	static char	*ptr_buff;
	int			new_line;


	printf("\nptr_buff al inicio: \"%s\"", ptr_buff);


	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ptr_ln = NULL;
	if (ptr_buff != NULL)
	{
		new_line = split_buff(&ptr_buff, &ptr_ln);
		if (new_line < 0)
			return (NULL);
		if (new_line == 1)
			return (ptr_ln);
	}

	
	// printf("\n ANTES DE IR A READ UNTIL --> ptr_ln: %p \"%s\"", &ptr_ln, ptr_ln);
	// printf("\n ANTES DE IR A READ UNTIL --> ptr_buff: %p \"%s\"", &ptr_buff, ptr_buff);

	ptr_ln = read_until_n_or_0(fd, &ptr_buff,  &ptr_ln);
	printf("\n despiues de read_until_n_or_0");
	return (ptr_ln);
}

int	main(void)
{
	char	*line;
	int		t;
	int		i;
	char	file_name[17];
	int		fd;

	t = 2;
	while (t < 3)
	{
		i = 1;
		sprintf(file_name, "%s%d%s", "tests/test_", t, ".txt");
		fd = open(file_name, O_RDONLY);
		printf("\n\n\n\n\nARCHIVO - %d - %s", t++, file_name);
		line = get_next_line(fd);
		while (line != NULL)
		{
			printf("\nline [%02d]: \"%s\"", i, line);
			i++;
			ft_free_ptr_ptr(&line);
			line = get_next_line(fd);
		}
		ft_free_ptr_ptr(&line);
		close(fd);
	}
	return (0);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("tests/read_error.txt", O_RDONLY);

// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);

// 	if (BUFFER_SIZE > 100) {
// 		printf("\nBUFFER_SIZE > 100");
// 		char *temp;
// 		do {
// 			temp = get_next_line(fd);
// 			free(temp);
// 		} while (temp != NULL);
// 	}

// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	close(fd);

// 	fd = open("tests/read_error.txt", O_RDONLY);
// 	line = get_next_line(fd);
// 	printf("\n\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);
// 	line = get_next_line(fd);
// 	printf("\nline: \"%s\"", line);
//  	ft_free_ptr_ptr(&line);

// 	return (0);
// }
