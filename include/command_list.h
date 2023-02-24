/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:46:50 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/24 01:23:53 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST
#define COMMAND_LIST

typedef struct s_cmd_list
{
	char	**cmd;
	int		infile;
	int		outfile;
	char 	*namehrd;
	struct s_cmd_list *next;
}	t_cmd_list;
#endif
