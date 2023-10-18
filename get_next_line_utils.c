/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juancho <juancho@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/18 07:59:02 by juancho          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	split_buff(char **ptr_buff, char **ptr_ln, char **ptr_nxt)
{
	char	*ptr_temp;
	int		check;
	int		brk_len;

	if (!ptr_buff) {
		printf("\nerror no hay ptr_buff");
		return (-1);
	}
	check = 0;
	ptr_temp = NULL;
	brk_len = ft_strlen_n(*ptr_buff);
	printf("\ndentro de SPLIT brk_len: %d", brk_len);
	printf("\ndentro de SPLIT buff: \"%s\"", *ptr_buff);

	if (brk_len > 0)
	{
		check += ft_ptr_cpy_ptr(ptr_buff, brk_len, 0, &ptr_temp);
		(*ptr_buff)[brk_len] = '\0';
	}
	check += ft_ptr_cpy_ptr(ptr_buff, 0, ft_strlen(*ptr_ln), ptr_ln);
	
	
	
	if (ft_strlen(*ptr_buff) == 0)
		printf("\ndentro de SPLIT ????????????????????????????????????????? ");
	ft_free_ptr_ptr(ptr_buff);
	if (ptr_nxt != NULL)
		ft_free_ptr_ptr(ptr_nxt);
	*ptr_nxt = ptr_temp;

	printf("\ndentro de SPLIT NXT: \"%s\"", *ptr_nxt);
	printf("\ndentro de SPLIT LINE: \"%s\"", *ptr_ln);



	if (check < 0)
		return (-1);
	if (brk_len > 0)
		return (1);
	return (0);
}

char	*read_until_n_or_0(int fd, char **ptr_ln, char **ptr_nxt)
{
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	rd_bytes = 1;
	new_or_end_line = 0;
	while (!new_or_end_line && rd_bytes > 0)
	{
		buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (!buff)
			return (NULL);
		// && buff[0] != '\0'
		printf("\nREAD /////////////////////////////////////////////////////");
		printf("\nREAD 1º rd_bytes: %d", rd_bytes);
		printf("\nREAD !new_or_end_line %d", !new_or_end_line);
		printf("\nREAD rd_bytes > 0 %d", rd_bytes > 0);
		
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		else if (rd_bytes == 0)
			return (free(buff), *ptr_ln);

			
		printf("\nREAD 2º rd_bytes: %d", rd_bytes);

		buff[rd_bytes] = '\0';
		printf("\nREAD rd_bytes: %d", rd_bytes);
		printf("\nREAD BUUFF: \"%s\"", buff);

		new_or_end_line = split_buff(&buff, ptr_ln, ptr_nxt);
		printf("\nREAD new_or_end_line: %d", new_or_end_line);
		printf("\nREAD NXT: \"%s\"", *ptr_nxt);
		printf("\nREAD LINE: \"%s\"", *ptr_ln);


		// if (rd_bytes == 0)
		// 	new_or_end_line = 1;



		if (new_or_end_line < 0)
			return (NULL);
		// else if (new_or_end_line == 1)
		else if (new_or_end_line == 1)
			return (*ptr_ln);
	}
	printf("\nREAD FUERAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");

	return (ft_free_ptr_ptr(ptr_ln), NULL);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_n(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1 + i);
		i++;
	}
	return (0);
}

void	ft_free_ptr_ptr(char **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}

int	ft_ptr_cpy_ptr(char **src, int s_ini, int d_ini, char **dst)
{
	char	*tmp;
	int		s_len;
	int		d;

	if (!src )
		return (-1);
	s_len = ft_strlen(*src);
	// printf("\nft_ptr_cpy_ptr s_len: %d", s_len);
	// printf("\nft_ptr_cpy_ptr s_ini: %d", s_ini);
	// printf("\nft_ptr_cpy_ptr d_ini: %d", d_ini);

	tmp = malloc(((s_len - s_ini) + d_ini + 1) * sizeof(char));
	if (tmp == NULL)
		return (-1);
	d = 0;
	while (dst && d_ini > 0 && d < d_ini)
	{
		tmp[d] = (*dst)[d];
		d++;
	}
	while ((*src)[s_ini] != '\0')
	{
		tmp[d] = (*src)[s_ini];
		s_ini++;
		d++;
	}
	tmp[d] = '\0';
	// printf("\nft_ptr_cpy_ptr d: %d", d);
	// printf("\nft_ptr_cpy_ptr tmp: \"%s\"", tmp);

	if (dst != NULL)
		ft_free_ptr_ptr(dst);
	*dst = tmp;
	return (0);
}
