/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 08:20:18 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/13 14:53:17 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

int	ft_max_long(char *str)
{
	int				sign;
	unsigned long	res;
	unsigned long	t;

	sign = 1;
	res = 0;
	while (*str == ' ' || (*str <= 13 && *str >= 9))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str <= '9' && *str >= '0')
	{
		t = (res * 10) + (*str - '0');
		if (res > t || t > (unsigned long)__LONG_MAX__ + (sign < 0))
			return (1);
		res = t;
		str++;
	}
	return (0);
}

int	check_arg(char *s)
{
	size_t	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (1);
		i++;
	}
	return (ft_max_long(s));
}

void	built_exit(t_data *f)
{
	if (!f->in_muti_pip)
		ft_putendl_fd("exit", 2);
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
			ft_putendl_fd("minishell: exit: too many arguments", 2);
		f->exit_status = 1;
	}
	else
	{
		tcsetattr(0, TCSANOW, &f->old_tty);
		exit(f->save_status);
	}
}
