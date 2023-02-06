/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:03:01 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/06 19:09:41 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_VAL_H
# define SET_VAL_H

typedef	struct s_vals
{
	char	*val;
	enum
	{
		V_STR,
		V_PIPE,
		V_APP,
		V_DIR,
		V_RDIR,
		V_HDK,
		V_EOF,
	}	token;
}	t_vals;

#endif