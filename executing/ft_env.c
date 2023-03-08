/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 10:06:45 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/07 15:44:42 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

char	**realloc_env(char **old_env, char *str)
{
	char	**new_env;

	new_env = ft_ultimate_join(old_env, str);
	if (!new_env)
		return (old_env);
	ft_free(old_env);
	return (new_env);
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
	char	*tmp;
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
	tmp = change_value(identifier, value, NULL);
	*env = realloc_env(my_env, tmp);
	free(tmp);
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
