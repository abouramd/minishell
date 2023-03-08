/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_string.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 15:41:14 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/07 15:41:18 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**sort_env(char **s, char **a, char **b, char *tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s && s[j])
	{
		i = 0;
		a = ft_split(s[j], '=');
		while (i < j)
		{
			b = ft_split(s[i], '=');
			if (ft_strcmp(a[0], b[0]) <= 0)
			{
				tmp = s[j];
				s[j] = s[i];
				s[i] = tmp;
			}
			ft_free(b);
			i++;
		}
		ft_free(a);
		j++;
	}
	return (s);
}

void	print_sort(char **s, int fd)
{
	size_t	i;
	size_t	h;

	i = 0;
	sort_env(s, NULL, NULL, NULL);
	while (s[i])
	{
		ft_putstr_fd("declare -x ", fd);
		h = 0;
		while (s[i][h] && s[i][h] != '=')
			ft_putchar_fd(s[i][h++], fd);
		if (s[i][h] == '=')
		{
			ft_putchar_fd(s[i][h++], fd);
			ft_putchar_fd('\"', fd);
			while (s[i][h])
				ft_putchar_fd(s[i][h++], fd);
			ft_putchar_fd('\"', fd);
		}
		ft_putchar_fd('\n', fd);
		i++;
	}
}
