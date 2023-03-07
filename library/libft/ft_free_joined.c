/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_joined.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/25 04:05:30 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/07 13:24:31 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free_joined(char *s1, char *s2, int d1, int d2)
{
	char	*p;

	p = NULL;
	if (s2 && s1)
		p = ft_strjoin(s1, s2);
	else if (!s1 && s2)
		p = ft_strdup(s2);
	else if (!s2 && s1)
		p = ft_strdup(s1);
	else if (!s2 && !s1)
		return (NULL);
	if (d1)
		free(s1);
	if (d2)
		free(s2);
	if (p == NULL)
		return (NULL);
	return (p);
}
