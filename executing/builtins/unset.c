/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:17:01 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/07 15:44:50 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static int	check_identifier(char *arg)
{
	size_t	i;

	i = 0;
	if (!ft_isalpha(arg[i]) && arg[i] != '_')
		return (1);
	i++;
	while (arg[i])
	{
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

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
		str = ft_free_joined(old_env[i - 1], str, 1, 1);
		str = ft_free_joined(h, str, 0, 1);
		i--;
	}
	free(old_env);
	save = ft_split(str, 127);
	free(str);
	return (save);
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

int	ft_unset(char *arg, t_data *f)
{
	if (check_identifier(arg))
		return (ft_puterr(arg, "not a valid identifier", 0), 1);
	ft_env_rm(arg, &f->my_env);
	return (0);
}

void	built_unset(t_data *f)
{
	size_t	i;
	int		es;

	i = 1;
	while (f->list_of_cmd->cmd[i])
	{
		es = ft_unset(f->list_of_cmd->cmd[i], f);
		if (es)
			f->exit_status = es;
		i++;
	}
}
