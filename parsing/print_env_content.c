/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:01:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/04 09:29:00 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*find_value(char *var, char **env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (env[i])
	{
		k = 0;
		while (env[i][k] && env[i][k] != '=')
			k++;
		if (!(ft_strncmp(env[i], var, k)) && ft_strlen(var) == (size_t)k)
		{
			j = ft_strlen(env[i]) - 1;
			while (env[i][j] != '=')
				j--;
			return (&env[i][j + 1]);	
		}
		i++;
	}
	return (NULL);
}
char	*take_care_of_dollar_sign(char	*line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == '$' && ft_isalpha(line[i + 1]))
			j++;
		i++;
	}
	str = malloc(i + j + 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (i != 0 && (line[i] == '$' && ft_isalpha(line[i - 1])))
		{
			str[j] = ' ';
			j++;
		}
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}

char	*befor_special(char *str)
{
	int		i;
	char	*s;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	s = malloc(i + 1);
	i = 0;
	while (str[i] && ft_isalnum(str[i]))
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}
char	*after_special(char *str)
{
	int		i;

	i = 0;
	while (str[i] && ft_isalnum(str[i]))
		i++;
	if (str[i] == '\0')
		return ("\0");
	return (&str[i]);
}

char	*print_env_content(char	*line, char **env)
{
	char	**str;
	char	*good_line;
	char	*save = NULL;
	int		i;
	int		j;
	char	*r;

	r = malloc(1);
	r[0] = '\0';
	i = 0;
	j = 0;
	good_line = take_care_of_dollar_sign(line);
	str = ft_split(good_line, ' ');
	free(good_line);
	while (str[i])
	{
		char *ptr;
		if (ft_strnstr(str[i], "$", 1) && ft_isalpha(str[i][1]))
			save = find_value(befor_special(str[i] + 1), env);
		ptr = r;
		if (save)
			r = ft_strjoin(r, save);
		else
			r = ft_strjoin(r, "\0");
		r = ft_strjoin(r, after_special(str[i] + 1));
		if (i != 0 && !ft_strnstr(str[i - 1], "$", 1))
			r = ft_strjoin(str[i - 1], r);
		free(ptr);
		i++;
	}
	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
	return (r);
}
