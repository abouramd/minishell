/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_c.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 23:11:15 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/07 15:41:43 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

void	ft_puterr(char *s, char *set, int n)
{
	write(2, "minishell: ", 11);
	if (s)
	{
		write(2, s, ft_strlen(s));
		write(2, ": ", 2);
	}
	if (set)
		write(2, set, ft_strlen(set));
	write(2, "\n", 1);
	if (n)
		exit(n);
}
