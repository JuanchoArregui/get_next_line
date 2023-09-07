/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/09/07 12:49:29 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *s, int rd_bytes, char *following)
{
	int	i;
	int	f;
	int	following_lenth;

	i = 0;
	f = 0;
	while (i < rd_bytes)
	{
		if (s[i] == '\0')
			return (1);
		if (s[i] == '\n')
		{
			following_lenth = rd_bytes - i;
			if (following_lenth > 1)
			{
				following = malloc((following_lenth ) * sizeof(char));
				if (!following)
					return (-1);
				while (i < rd_bytes)
				{
					following[f] = s[i];
					i++;
					f++;
				}
				following[following_lenth] = '\0';
			}
			return (1);
		}
		i++;
	}
	return (0);
}

char	*read_until_new_or_end_line(int fd, char *next_line, char *following)
{
	printf("\n");
	printf("\n");
	
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	rd_bytes = 1;
	new_or_end_line = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	if (following)
	{
		next_line = following;
		printf("\n--->following: %s", following);
	}
	else
		printf("\n--->NO following");


	// {
	// 	if (!next_line)
	// 	{
	// 		next_line = (char *)malloc(1 * sizeof(char));
	// 		if (!next_line)
	// 			return (NULL);
	// 		next_line[0] = '\0';
	// 	}
	// 	next_line = ft_read_join(following, next_line);
	// }

	while (!new_or_end_line && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			printf("\nERROR no rd_bytes");
			return (free(buff), NULL);
		}

		buff[rd_bytes] = '\0';
		printf("\n--------->buff: %s", buff);
		printf("\n--------->next_line: %s", next_line);
		printf("\n--------->");

		new_or_end_line = find_new_or_end_line(buff, rd_bytes, following);
		if (new_or_end_line == -1)
			return (NULL);
		next_line = ft_read_join(next_line, buff);


		// printf("\nbuff: %s", buff);
		// printf("\nrd_bytes: %i", rd_bytes);
		// printf("\nread_content: %s", read_content);
		// printf("\n");
	}
	return (free(buff), next_line);
}

char	*ft_read_join(char *next_line, char *buff)
{
	size_t	i;
	size_t	j;
	size_t	total_length;
	char	*str;

	if (!buff)
		return (NULL);
	if (!next_line)
	{
		next_line = (char *)malloc(1 * sizeof(char));
		if (!next_line)
			return (NULL);
		next_line[0] = '\0';
		printf("\nPRIMERA VEZ!!!!!!!!!!!!");
		total_length = ft_strlen(buff) + 1;
	}
	else
		total_length = ft_strlen(next_line) + ft_strlen(buff) + 1;
	// printf("\ntotal_length: %zu", total_length);
	
	
	str = malloc(sizeof(char) * total_length);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	//esto para el posible contenido previo
	printf("\nOLD --> %s", next_line);
	while (next_line[i] != '\0')
	{
		// printf("\ni: %zu", i);
		str[i] = next_line[i];
		i++;
		// printf(" - %s", str);
	}
	free(next_line);


	//esto es para el nuevo contenido
	// printf("\nNEW");
	while (buff[j] != '\0' && buff[j] != '\n')
	{
		// printf("\ni: %zu", i);
		str[i++] = buff[j++];
		// printf(" - %s", str);
	}
	
	str[i] = '\0';
	return (str);
}

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
		i++;
	return (i);
}
