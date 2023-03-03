/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:21 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/01 14:44:29 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	builtins(t_data *f)
{
	if (f->list_of_cmd->cmd && *f->list_of_cmd->cmd)
	{
		if (!ft_strcmp(f->list_of_cmd->cmd[0], "pwd"))
			return (built_pwd(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "cd"))
			return (built_cd(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "unset"))
			return (built_unset(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "export"))
			return (built_export(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "exit"))
			return (built_exit(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "echo"))
			return (built_echo(f), 1);
		else if (!ft_strcmp(f->list_of_cmd->cmd[0], "env"))
			return (built_env(f), 1);
	}
	return (0);
}
