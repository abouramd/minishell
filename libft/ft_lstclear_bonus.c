/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 21:58:28 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/19 13:39:19 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*p;
	t_list	*t;

	if (!lst || !del)
		return ;
	p = *lst;
	while (p)
	{
		t = (*p).next;
		ft_lstdelone(p, *del);
		p = t;
	}
	*lst = NULL;
}
