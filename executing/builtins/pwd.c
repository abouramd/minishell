/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:17:16 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/13 08:50:17 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	built_pwd(t_data *f)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX - 1) == NULL)
	{	
		if (ft_find_env("PWD", f->my_env))
		{
			ft_putendl_fd(ft_find_env("PWD", f->my_env),
				f->list_of_cmd->outfile);
		}
		else
		{
			perror("getcwd");
			f->exit_status = 1;
		}
	}
	else
		ft_putendl_fd(pwd, f->list_of_cmd->outfile);
}
