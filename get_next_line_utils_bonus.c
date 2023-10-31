/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 14:04:23 by jarregui          #+#    #+#             */
/*   Updated: 2023/10/31 15:49:39 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	if (!src)
		return (-1);
	s_len = ft_strlen(*src);
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
		tmp[d++] = (*src)[s_ini++];
	tmp[d] = '\0';
	if (dst != NULL)
		ft_free_ptr_ptr(dst);
	*dst = tmp;
	return (0);
}
