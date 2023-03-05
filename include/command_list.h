/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_list.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/16 13:46:50 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/05 17:35:04 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LIST_H
# define COMMAND_LIST_H

typedef struct s_cmd_list
{
	char				**cmd;
	int					infile;
	int					outfile;
	char				*infile_name;
	int					infile_errno;
	char				*outfile_name;
	int					outfile_errno;
	struct s_cmd_list	*next;
}						t_cmd_list;
#endif
