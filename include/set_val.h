/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:03:01 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/04 19:07:17 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_VAL_H
# define SET_VAL_H

typedef	struct s_vals
{
	enum
	{
		V_STR,
		V_PIPE,
		V_APP,
		V_DIR,
		V_RDIR,
		V_HDK,
		V_EOF,
	};
}	t_vals;

#endif