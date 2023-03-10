/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_val.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 19:03:01 by zasabri           #+#    #+#             */
/*   Updated: 2023/03/10 09:36:44 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SET_VAL_H
# define SET_VAL_H

typedef struct s_vals
{
	char	*val;
	enum
	{
		V_STR,
		V_PIPE,
		V_APP,
		V_IN_RDIR,
		V_OUT_RDIR,
		V_HDK,
		V_EOF,
	} e_token;
}			t_vals;

#endif
