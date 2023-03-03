/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 17:17:58 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/25 10:04:13 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
#endif //BUFFER_SIZE

int	str_chr(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		if (s[i++] == c)
			return (0);
	return (1);
}

char	*join_str(char *s1, char *s2)
{
	char	*r;
	int		len1;
	int		len2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(1);
		if (!s1)
			return (NULL);
		*s1 = '\0';
	}
	len1 = 0;
	len2 = 0;
	while (s1[len1] || s2[len2])
	{
		if (s1[len1])
			len1++;
		if (s2[len2])
			len2++;
	}
	r = (char *)malloc(len1 + len2 + 1);
	if (r)
	{
		j = len1;
		len1 = 0;
		len2 = 0;
		while (s1[len1] || s2[len2])
		{
			if (s1[len1])
				r[i++] = s1[len1++];
			if (s2[len2])
				r[j++] = s2[len2++];
		}
		r[j] = '\0';
	}
	free(s1);
	return (r);
}

char	*read_file(char *stock, int fd)
{
	char	*buffer;
	int		i;

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
		while (str_chr(buffer, '\n'))
		{
			i = read(fd, buffer, BUFFER_SIZE);
			if (i == -1)
			{
				if (stock)
					free(stock);
				free(buffer);
				return (NULL);
			}
			if (i == 0)
				break ;
			buffer[i] = '\0';
			stock = join_str(stock, buffer);
			if (!stock)
				break ;
		}
		free(buffer);
	}
	return (stock);
}

char	*get_ret_line(char *s, size_t *n)
{
	size_t	i;
	char	*line;

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
	{
		line[i] = s[i];
		i++;
	}
	if (s[i] == '\n')
	{
		line[i] = s[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_stock(char *stock, size_t start)
{
	char	*s;
	size_t	n;
	size_t	i;

	if (!stock[start - 1])
	{
		free(stock);
		return (NULL);
	}
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

