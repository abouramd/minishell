/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:06:45 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/01 08:49:54 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**rm_var(char **old_env)
{
	char	*str;
	char	**save;
	char	h[2];
	size_t	i;

	h[0] = 127;
	h[1] = 0;
	i = 0;
	while (old_env[i])
		i++;
	str = NULL;
	while (i > 0)
	{
		str = ft_free_joined(old_env[i - 1], str, 0, 1);
		str = ft_free_joined(h, str, 0, 1);
		i--;
	}
	save = ft_split(str, 127);
	if (!save)
		return (old_env);
	ft_free(old_env);
	return (save);
}

char	**realloc_env(char **old_env, char *str)
{
	char	**new_env;

	new_env = ft_ultimate_join(old_env, str);
	if (!new_env)
		return (old_env);
	ft_free(old_env);
	return (new_env);
}

void	ft_env_rm(char *elem, char ***env)
{
	char	**my_env;
	char	**s;
	char	*tmp;
	size_t	index;

	my_env = *env;
	index = 0;
	while (my_env && my_env[index])
	{
		s = ft_split(my_env[index], '=');
		if (!ft_strcmp(s[0], elem))
		{
			tmp = ft_strdup("");
			if (!tmp)
				exit(1);
			free(my_env[index]);
			my_env[index] = tmp;
			*env = rm_var(my_env);
			ft_free(s);
			break ;
		}
		ft_free(s);
		index++;
	}
}

char	*ft_find_env(char *elem, char **my_env)
{
	char	**s;
	char	*t;
	size_t	index;

	index = 0;
	while (my_env && my_env[index])
	{
		s = ft_split(my_env[index], '=');
		if (!ft_strcmp(s[0], elem))
		{
			ft_free(s);
			t = ft_strchr(my_env[index], '=');
			if (t)
				t++;
			return (t);
		}
		ft_free(s);
		index++;
	}
	return (NULL);
}

char	*change_value(char *identifier, char *value, char *s)
{
	char	*var;

	if (value)
	{
		var = ft_strjoin(identifier, "=");
		if (!var)
			return (s);
		var = ft_free_joined(var, value, 1, 0);
		if (!var)
			return (s);
	}
	else
	{
		var = ft_strdup(identifier);
		if (!var)
			return (s);
	}
	if (s)
		free(s);
	return (var);
}

void	ft_env_add(char *identifier, char *value, char ***env)
{
	char	**my_env;
	char	**s;
	size_t	index;

	my_env = *env;
	index = 0;
	while (my_env && my_env[index])
	{
		s = ft_split(my_env[index], '=');
		if (!ft_strcmp(s[0], identifier))
		{
			ft_free(s);
			my_env[index] = change_value(identifier, value, my_env[index]);
			return ;
		}
		ft_free(s);
		index++;
	}
	*env = realloc_env(my_env, change_value(identifier, value, NULL));
}
// void	ft_env_add(char *elem, char ***env)
// {
// 	char	**my_env;
// 	char	**s;
// 	char	**t;
// 	char	*tmp;
// 	size_t	index;

// 	my_env = *env;
// 	index = 0;
// 	t = ft_split(elem, '=');
// 	while (my_env && my_env[index])
// 	{
// 		s = ft_split(my_env[index], '=');
// 		if (!ft_strcmp(s[0], t[0]))
// 		{
// 			if (ft_strchr(elem, '='))
// 			{
// 				tmp = ft_strdup(elem);
// 				if (!tmp)
// 					exit(1);
// 				free(my_env[index]);
// 				my_env[index] = tmp;
// 			}
// 			ft_free(s);
// 			ft_free(t);
// 			return ;
// 		}
// 		ft_free(s);
// 		index++;
// 	}
// 	*env = realloc_env(my_env, elem);
// 	ft_free(t);
// }

// void appand_env(char *elem, char ***env)
// {
// 	char	**my_env;
// 	char	**s;
// 	char	**t;
// 	char	*tmp;
// 	size_t	index;

// 	my_env = *env;
// 	index = 0;
// 	t = ft_split(elem, '=');
// 	while (my_env && my_env[index])
// 	{
// 		s = ft_split(my_env[index], '=');
// 		if (!ft_strcmp(s[0], t[0]))
// 		{
// 			if (ft_strchr(elem, '='))
// 			{
// 				tmp = ft_strdup(elem);
// 				if (!tmp)
// 					exit(1);
// 				free(my_env[index]);
// 				my_env[index] = tmp;
// 			}
// 			ft_free(s);
// 			ft_free(t);
// 			return ;
// 		}
// 		ft_free(s);
// 		index++;
// 	}
// 	*env = realloc_env(my_env, elem);
// 	ft_free(t);
// }
