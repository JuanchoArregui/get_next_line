/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:27:04 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/12 23:38:47 by juancho          ###   ########.fr       */
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
int	    find_new_or_end_line(char *buff, int rd_bytes, char **ptr_next, char **ptr_line);
char	*read_until_new_or_end_line(int fd, char **ptr_line, char **ptr_next);

char	*ft_read_join(char **ptr_line, char *buff);

size_t	ft_strlen(char *s);
void	free_ptr(char *ptr);
void	free_ptr_ptr(char **ptr);



#endif
