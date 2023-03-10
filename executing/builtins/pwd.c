/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:17:16 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/10 11:47:11 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	built_pwd(t_data *f)
{
	char	pwd[PATH_MAX];

	if (getcwd(pwd, PATH_MAX - 1) == NULL)
		ft_strlcpy(pwd, "", 1);
	ft_putendl_fd(pwd, f->list_of_cmd->outfile);
}
