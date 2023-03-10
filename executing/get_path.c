/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:41:54 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/10 11:38:42 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	count_size_of_path(char *s)
{
	size_t	size;
	size_t	i;

	size = 0;
	i = 0;
	if (s[i] == '\0')
		return (1);
	if (s[i] == ':')
	{
		size++;
		size++;
		i++;
	}
	while (s[i])
	{
		if (s[i] == ':' && s[i - 1] == ':')
			size++;
		size++;
		i++;
	}
	if (s[i - 1] == ':')
		size++;
	return (size);
}

void	fill_path(char *p, char *s)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (s[n] != '\0')
	{
		if (s[n] == ':')
		{
			p[i++] = '.';
			p[i++] = s[n++];
		}
		while (s[n])
		{
			if (s[n] == ':' && s[n - 1] == ':')
				p[i++] = '.';
			p[i++] = s[n++];
		}
		if (s[n - 1] == ':')
			p[i++] = '.';
	}
	else
		p[i++] = '.';
	p[i] = '\0';
}

char	*path_get(char *s)
{
	char	*p;

	s = ft_strdup(s);
	if (!s)
		ft_puterr("ft_strdup", "malloc !!", 1);
	p = malloc(count_size_of_path(s) + 1);
	if (!p)
		ft_puterr("malloc", "malloc !!", 1);
	fill_path(p, s);
	free(s);
	return (p);
}

char	**split_path(t_data *d, int *choose)
{
	int		i;
	char	**s;
	char	*tmp;

	i = 0;
	s = NULL;
	while (d->my_env && d->my_env[i])
	{
		if (ft_strncmp(d->my_env[i], "PATH=", 5) == 0)
		{
			tmp = path_get(&d->my_env[i][5]);
			s = ft_split(tmp, ':');
			free(tmp);
			break ;
		}
		i++;
	}
	if (!s)
	{
		s = ft_ultimate_join(NULL, ".");
		*choose = 1;
	}
	return (s);
}
