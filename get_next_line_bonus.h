/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:04:09 by jarregui          #+#    #+#             */
/*   Updated: 2023/11/02 10:59:37 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif

# ifndef MAX_THREADS
#  define MAX_THREADS 4092
# endif

# include <unistd.h>//this allows Read function
# include <stdlib.h>//this allows Malloc function
# include <fcntl.h>//this allows File Control functions, opend, close
# include <stdio.h>//this allows PRINTF function

int		split_buff(char **ptr_buff, char **ptr_ln, char **ptr_nxt);
char	*read_until_n_or_0(int fd, char **ptr_ln, char **ptr_nxt);
char	*get_next_line(int fd);
int		ft_strlen(char *s);
int		ft_strlen_n(char *s);
void	ft_free_ptr_ptr(char **ptr);
int		ft_ptr_cpy_ptr(char **src, int s_ini, int d_ini, char **dst);

#endif
