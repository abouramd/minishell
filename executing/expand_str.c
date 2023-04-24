/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:53:47 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/13 12:22:00 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	**add_args(char **save, char *expanded_str, size_t *x, size_t *y)
{
	char	**tmp;
	size_t	i;
	char	c;

	i = *x;
	tmp = save;
	c = 0;
	save = ft_ultimate_join(tmp, "");
	ft_free(tmp);
	while (expanded_str && expanded_str[i])
	{
		if ((expanded_str[i] == '\t' || expanded_str[i] == ' ') && c == 0)
			break ;
		if ((expanded_str[i] == '\"' || expanded_str[i] == '\'') && c == 0)
			c = expanded_str[i];
		else if (c && expanded_str[i] == c)
			c = 0;
		else
			save[*y] = add_str(save[*y], expanded_str[i]);
		i++;
	}
	*x = i;
	return (save);
}

static char	**ft_split_expand(char *expanded_str)
{
	char	**save;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	save = NULL;
	while (expanded_str && (expanded_str[i] == ' ' || expanded_str[i] == '\t'))
		i++;
	while (expanded_str && expanded_str[i])
	{
		save = add_args(save, expanded_str, &i, &j);
		while (expanded_str[i] == ' ' || expanded_str[i] == '\t')
			i++;
		j++;
	}
	return (free(expanded_str), save);
}

static void	ft_qoute_handel(char c, char *set)
{
	if ((c == '\"' || c == '\'') && *set == 0)
		*set = c;
	else if (*set && c == *set)
		*set = 0;
}

char	**ft_expand_str(t_data *f, char *s)
{
	char	*expanded_str;
	size_t	i;
	char	c;
	char	**tmp;

	c = 0;
	i = 0;
	expanded_str = NULL;
	while (s && s[i])
	{
		ft_qoute_handel(s[i], &c);
		if (c != '\'' && s[i] == '$')
		{
			if (c == 0 && (s[i + 1] == '\'' || s[i + 1] == '\"'))
				i++;
			else
				expanded_str = ft_replace_val(f, s, expanded_str, &i);
			continue ;
		}
		else
			expanded_str = add_str(expanded_str, s[i]);
		i++;
	}
	tmp = ft_split_expand(expanded_str);
	return (tmp);
}
