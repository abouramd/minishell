/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:20:18 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/28 11:20:48 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	check_arg(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '-' && s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (0);
}

void	built_exit(t_data *f)
{
	ft_putendl_fd("exit", 1);
	if (f->list_of_cmd->cmd[1] != NULL)
	{
		if (f->list_of_cmd->cmd[2] == NULL
			&& check_arg(f->list_of_cmd->cmd[1]) == 0)
		{
			tcsetattr(0, TCSANOW, &f->old_tty);
			exit(ft_atoi(f->list_of_cmd->cmd[1]));
		}
		else if (check_arg(f->list_of_cmd->cmd[1]) == 1)
		{
			tcsetattr(0, TCSANOW, &f->old_tty);
			ft_putendl_fd("minishell: exit: numeric argument required", 2);
			exit(255);
		}
		else
		{
			ft_putendl_fd("minishell: exit: too many arguments", 2);
			f->exit_status = 1;
		}
	}
	else
		exit(0);
}
