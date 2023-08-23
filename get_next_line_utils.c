/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jarregui <jarregui@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/22 15:26:31 by jarregui          #+#    #+#             */
/*   Updated: 2023/08/23 22:53:59 by jarregui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	find_new_or_end_line(char *s, int rd_bytes)
{
	int	i;

	i = 0;
	while (i < rd_bytes)
	{
		if (s[i] == '\0' || s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*read_until_new_or_end_line(int fd, char *read_content)
{
	printf("\nread_until_new_or_end_line");
	
	char	*buff;
	int		rd_bytes;
	int		new_or_end_line;

	rd_bytes = 1;
	new_or_end_line = 0;
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	printf("\n--->new_or_end_line: %i", new_or_end_line);
	printf("\n--->rd_bytes: %i", rd_bytes);

	while (!new_or_end_line && rd_bytes > 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
			return (free(buff), NULL);
		buff[rd_bytes] = '\0';
		new_or_end_line = find_new_or_end_line(buff, rd_bytes);
		read_content = ft_strjoin(read_content, buff);


		// printf("\nbuff: %s", buff);
		// printf("\nrd_bytes: %i", rd_bytes);
		// printf("\nread_content: %s", read_content);
		// printf("\n");
	}
	free(buff);
	return (read_content);
}

char	*ft_strjoin(char *read_content, char *buff)
{
	// printf("\n\nft_strjoin, %s, %s",read_content, buff );
	
	size_t	i;
	size_t	j;
	size_t	total_length;
	char	*str;

	// if (!read_content)
	// {
	// 	read_content = (char *)malloc(1 * sizeof(char));
	// 	read_content[0] = '\0';
	// printf("\nPRIMERA VEZ!!!!!!!!!!!!");

	// }
	if (!buff)
		return (NULL);
	if (!read_content)
		total_length = ft_strlen(buff) + 1;
	else
		total_length = ft_strlen(read_content) + ft_strlen(buff) + 1;
	// printf("\ntotal_length: %zu", total_length);
	
	
	str = malloc(sizeof(char) * total_length);
	if (str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	//esto para el posible contenido previo
	if (read_content)
	{
		// printf("\nOLD --> %s", read_content);
		while (read_content[i] != '\0')
		{
			// printf("\ni: %zu", i);
			str[i] = read_content[i];
			i++;
			// printf(" - %s", str);
		}
	}
	//esto es para el nuevo contenido
	// printf("\nNEW");
	while (buff[j] != '\0' && buff[j] != '\n')
	{
		// printf("\ni: %zu", i);
		str[i++] = buff[j++];
		// printf(" - %s", str);
	}
	
	str[i] = '\0';
	// str[ft_strlen(read_content) + ft_strlen(buff)] = '\0';
	if (read_content)
		free(read_content);

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
