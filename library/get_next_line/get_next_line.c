/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/05 21:17:11 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/08 10:31:40 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*keep_read(char *stock, int fd, char *buffer)
{
	int	i;

	while (str_chr(buffer, '\n'))
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			if (stock)
				free(stock);
			return (NULL);
		}
		if (i == 0)
			break ;
		buffer[i] = '\0';
		stock = join_str(stock, buffer);
		if (!stock)
			break ;
	}
	return (stock);
}

char	*read_file(char *stock, int fd)
{
	char	*buffer;

	if (str_chr(stock, '\n'))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
		{
			if (stock)
				free(stock);
			return (NULL);
		}
		buffer[0] = '\0';
		stock = keep_read(stock, fd, buffer);
		free(buffer);
	}
	return (stock);
}

char	*get_ret_line(char *s, size_t *n)
{
	size_t	i;
	size_t	k;
	char	*line;

	k = 0;
	i = 0;
	if (s[i] == '\0')
		return (NULL);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	*n = i;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		line[k++] = s[i++];
	if (s[i] == '\n')
		line[k++] = s[i++];
	line[k++] = '\0';
	return (line);
}

char	*get_stock(char *stock, size_t start)
{
	char	*s;
	size_t	n;
	size_t	i;

	if (!stock[start - 1])
		return (free(stock), NULL);
	n = start;
	i = 0;
	while (stock[n++])
		i++;
	s = malloc(i + 1);
	if (!s)
	{
		free(stock);
		return (NULL);
	}
	i = 0;
	n = start;
	while (stock[n])
		s[i++] = stock[n++];
	s[i++] = '\0';
	free(stock);
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	size_t		i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stock = read_file(stock, fd);
	if (!stock)
		return (NULL);
	line = get_ret_line(stock, &i);
	if (!line)
	{
		free(stock);
		stock = NULL;
		return (NULL);
	}
	stock = get_stock(stock, i);
	return (line);
}

// int main()
// {
//     int fd;
//     char *line = "";

//     fd = open("get_next_line.c", O_RDONLY);
//     while (line)
//     {
//         line = get_next_line(fd);
//         printf("%s", line);
//         if (line)
//             free(line);
//     }
//     system("leaks a.out");
//     return (0);
// }
