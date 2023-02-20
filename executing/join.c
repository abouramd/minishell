/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 16:09:46 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/18 03:32:05 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_free(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
}

int	my_strstr(char *s, char *set)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s && s[i])
	{
		j = 0;
		while (s[i + j] == set[j] && s[i + j])
		{
			if (!set[j + 1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

char	*myjoin(char *s1, char *s2)
{
	char	*p;
	int		i;
	int		j;
	int		k;

	k = 0;
	if (!s1 || !s1)
		return (NULL);
	p = (char *)malloc((ft_strlen(s2) + ft_strlen(s1) + 1) * sizeof(char));
	if (!p)
	{
		free(s1);
		return (NULL);
	}
	j = 0;
	i = 0;
	while (s1[i])
		p[k++] = s1[i++];
	while (s2[j])
		p[k++] = s2[j++];
	p[k] = '\0';
	free(s1);
	return (p);
}
