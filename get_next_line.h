/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:27:04 by jarregui          #+#    #+#             */
/*   Updated: 2023/11/21 15:45:14 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <unistd.h>//this allows Read function
# include <stdlib.h>//this allows Malloc function
# include <fcntl.h>//this allows File Control functions, opend, close
# include <stdio.h>//this allows PRINTF function

int		split_buff(char **ptr_buff, char **ptr_ln);
char	*read_until_n_or_0(int fd, char **ptr_buff, char **ptr_ln);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
int		ft_strlen_n(char *s);
void	ft_free_ptr_ptr(char **ptr);
int		ft_ptr_cpy_ptr(char **src, int s_ini, int d_ini, char **dst);

#endif
