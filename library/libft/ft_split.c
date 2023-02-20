/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 13:46:24 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/19 11:59:38 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	char_count(char const *s, char c)
{
	size_t	index;
	size_t	count_t;

	index = 0;
	count_t = 0;
	while (s[index] && s[index] == c)
		index++;
	while (s[index])
	{
		while (s[index] && s[index] != c)
			index++;
		while (s[index] && s[index] == c)
			index++;
		count_t++;
	}
	return (count_t);
}

static size_t	new_i(char const *s, char c, size_t index)
{
	while (s[index] && s[index] == c)
		index++;
	return (index);
}

static size_t	splittostr(char const *s, char c, char **p)
{
	size_t	index;
	size_t	x;
	size_t	m;
	size_t	count_t;

	index = 0;
	count_t = 0;
	index = new_i(s, c, index);
	while (s[index])
	{
		m = 0;
		x = index;
		while (s[index] && s[index] != c)
			index++;
		p[count_t] = (char *)malloc(index - x + 1);
		if (!p[count_t])
			return (count_t);
		while (x < index)
			p[count_t][m++] = s[x++];
		p[count_t][m] = '\0';
		index = new_i(s, c, index);
		count_t++;
	}
	return (count_t);
}

char	**ft_split(char const *s, char c)
{
	char	**p;
	size_t	c_c;
	size_t	m;

	if (!s)
		return (NULL);
	c_c = char_count(s, c);
	p = (char **)malloc(sizeof(char *) * (c_c + 1));
	if (!p)
		return (NULL);
	p[c_c] = NULL;
	if (c_c == 0)
		return (p);
	m = splittostr(s, c, p);
	if (m != c_c)
	{
		while (m > 0)
		{
			free (p[m - 1]);
			m--;
		}
		free (p);
		return (NULL);
	}
	return (p);
}
