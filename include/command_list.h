/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:46:50 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/20 01:08:12 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST
#define COMMAND_LIST

typedef struct s_cmd_list
{
	char	**cmd;
	int		infile;
	int		outfile;
	struct s_cmd_list *next;
}	t_cmd_list;
#endif
