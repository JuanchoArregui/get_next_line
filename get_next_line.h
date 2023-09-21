/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:27:04 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/21 13:20:06 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

# include <unistd.h>//this allows Read function
# include <stdlib.h>//this allows Malloc function
# include <fcntl.h>//this allows File Control functions, opend, close
# include <stdio.h>//this allows PRINTF function

char	*get_next_line(int fd);
int		find_n_or_0(char *buff, int rd_bytes, char **ptr_next, char **ptr_line);
char	*read_until_n_or_0(int fd, char **ptr_line, char **ptr_next);


int		check_ptr_next(char **ptr_line, char **ptr_next);

size_t	ft_strlen(char *s);
size_t	ft_strlen_line(char *s);
void	ft_free_ptr_ptr(char **ptr);
int		ft_ptr_cpy_ptr(char **src, size_t start, size_t end, char **dest);



#endif
