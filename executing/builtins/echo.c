/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 05:23:31 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/21 08:56:48 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"


int ch_flag(char *s)
{
    size_t i = 0;
    
    if (s[i] != '-')
        return 0;
    i++;
    if (s[i] != 'n')
        return 0;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

void print_list(t_data *f, size_t i)
{
    while (f->list_of_cmd->cmd[i])
    {
        ft_putstr_fd(f->list_of_cmd->cmd[i], f->list_of_cmd->outfile);
        i++;
        if (f->list_of_cmd->cmd[i] != NULL)
            ft_putstr_fd(" ", f->list_of_cmd->outfile);
    }
}

void built_echo(t_data *f)
{
    size_t i = 1;

    if (f->list_of_cmd->cmd[1] == NULL)
        ft_putendl_fd("", f->list_of_cmd->outfile);
    else 
    {
        if (ch_flag(f->list_of_cmd->cmd[i]) == 1)
        {
            while (f->list_of_cmd->cmd[i] && ch_flag(f->list_of_cmd->cmd[i]) == 1)
                i++;
            print_list(f, i);
        }
        else
        {
            print_list(f, i);
            ft_putstr_fd("\n", f->list_of_cmd->outfile);
        }
    }
}
