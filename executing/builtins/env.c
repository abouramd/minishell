/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:21:44 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/28 11:21:47 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	built_env(t_data *f)
{
	size_t i = 0;
	if (f->list_of_cmd->cmd[1])
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		f->exit_status = 1;
		return ;
	}
	while (f->my_env && f->my_env[i])
	{
		if (ft_strchr(f->my_env[i], '='))
			ft_putendl_fd(f->my_env[i], f->list_of_cmd->outfile);
		i++;
	}
}