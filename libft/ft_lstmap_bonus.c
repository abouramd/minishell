/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 13:02:36 by abouramd          #+#    #+#             */
/*   Updated: 2022/10/20 13:04:06 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*t;
	t_list	*new_head;

	if (!lst || !f || !del)
		return (NULL);
	t = lst;
	new_node = ft_lstnew((*f)((*t).content));
	if (!new_node)
		return (NULL);
	new_head = new_node;
	while ((*t).next)
	{
		t = (*t).next;
		(*new_node).next = ft_lstnew((*f)((*t).content));
		if (!(*new_node).next)
		{
			ft_lstclear(&new_head, del);
			return (NULL);
		}
		new_node = (*new_node).next;
	}
	return (new_head);
}
