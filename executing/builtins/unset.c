/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:17:01 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/28 08:17:02 by abouramd         ###   ########.fr       */
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
