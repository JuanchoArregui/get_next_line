/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:27:04 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/18 07:57:14 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1111111111
# endif

# include <unistd.h>//this allows Read function
# include <stdlib.h>//this allows Malloc function
# include <fcntl.h>//this allows File Control functions, opend, close
# include <stdio.h>//this allows PRINTF function

char	*get_next_line(int fd);
char	*read_until_n_or_0(int fd, char **ptr_ln, char **ptr_nxt);
int	    split_buff(char **ptr_buff, char **ptr_ln, char **ptr_nxt);



// int		find_n_or_0(char **buff, int rd_bytes, char **ptr_nxt, char **ptr_ln);
// int		check_ptr_nxt(char **ptr_ln, char **ptr_nxt, int nxt_len, int brk_len);


int		ft_strlen(char *s);
int		ft_strlen_n(char *s);
void	ft_free_ptr_ptr(char **ptr);
int		ft_ptr_cpy_ptr(char **src, int s_ini, int d_ini, char **dst);

#endif
