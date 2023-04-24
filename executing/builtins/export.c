/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:17:50 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/13 10:52:39 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_check_in_env(char *elem, char **my_env)
{
	char	**s;
	size_t	index;

	index = 0;
	while (my_env && my_env[index])
	{
		s = ft_split(my_env[index], '=');
		if (!ft_strcmp(s[0], elem))
		{
			ft_free(s);
			return (1);
		}
		ft_free(s);
		index++;
	}
	return (0);
}

static int	app_or_def(char *arg, int *type)
{
	if (arg[0] == '+' && arg[1] == '=')
	{
		*type = APPAND_ENV;
		return (2);
	}
	if (arg[0] == '=')
	{
		*type = DEFIN_ENV;
		return (1);
	}
	return (0);
}

static char	*check_identifier(char *arg, int *type, char **value)
{
	size_t	i;
	char	*identifier;
	int		tmp;

	identifier = NULL;
	i = 0;
	while (arg[i])
	{
		tmp = app_or_def(&arg[i], type);
		i += tmp;
		if (tmp != 0)
			break ;
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
		{
			if (identifier)
				free(identifier);
			return (NULL);
		}
		identifier = add_str(identifier, arg[i]);
		i++;
	}
	if (*type == APPAND_ENV || *type == DEFIN_ENV)
		*value = ft_strdup(&arg[i]);
	return (identifier);
}

int	ft_export(t_data *f, char *arg)
{
	char	*identifier;
	char	*value;
	int		choose;

	identifier = NULL;
	choose = 0;
	value = NULL;
	if (!ft_isalpha(arg[0]) && arg[0] != '_')
		return (ft_puterr(arg, "not a valid identifier", 0), 1);
	identifier = check_identifier(arg, &choose, &value);
	if (!identifier)
		return (ft_puterr(arg, "not a valid identifier", 0), 1);
	if (choose == APPAND_ENV)
	{
		value = ft_free_joined(ft_find_env(identifier, f->my_env), value, 0, 1);
		ft_env_add(identifier, value, &f->my_env);
	}
	else if (choose == DEFIN_ENV)
		ft_env_add(identifier, value, &f->my_env);
	else if (!ft_check_in_env(identifier, f->my_env))
		f->my_env = realloc_env(f->my_env, identifier);
	free(identifier);
	if (value)
		free(value);
	return (0);
}

void	built_export(t_data *f)
{
	size_t	i;
	int		es;
	char	**en;

	i = 1;
	if (f->list_of_cmd->cmd[1] == NULL)
	{
		en = alloc_env(f->my_env);
		print_sort(en, f->list_of_cmd->outfile);
		ft_free(en);
	}
	else
	{
		while (f->list_of_cmd->cmd[i])
		{
			es = ft_export(f, f->list_of_cmd->cmd[i]);
			if (es)
				f->exit_status = es;
			i++;
		}
	}
}
