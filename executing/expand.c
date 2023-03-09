/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:53:47 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/08 19:06:43 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

static char	*fill_var(char *val, char *expanded_str)
{
	size_t	j;

	j = 0;
	while (val && val[j])
		expanded_str = add_str(expanded_str, val[j++]);
	return (expanded_str);
}

char	*ft_replace_val(t_data *f, char *str, char *expanded_str, size_t *index)
{
	char	*val;
	char	*id;
	size_t	i;

	id = NULL;
	i = *index + 1;
	if (str && str[i] == '?')
	{
		val = ft_itoa(f->exit_status);
		expanded_str = fill_var(val, expanded_str);
		free(val);
		i++;
	}
	else if (str && !ft_isalnum(str[i]) && str[i] != '_')
		expanded_str = add_str(expanded_str, '$');
	else
	{
		while (str && (ft_isalnum(str[i]) || str[i] == '_'))
			id = add_str(id, str[i++]);
		expanded_str = fill_var(ft_find_env(id, f->my_env), expanded_str);
		free(id);
	}
	*index = i;
	return (expanded_str);
}

char	*ft_expand_in_here_doc(t_data *f, char *s, int type)
{
	char	*expanded_str;
	size_t	i;

	if (type == 0)
		return (s);
	expanded_str = NULL;
	i = 0;
	if (s)
	{
		while (s && s[i])
		{
			if (s[i] == '$')
				expanded_str = ft_replace_val(f, s, expanded_str, &i);
			else
				expanded_str = add_str(expanded_str, s[i++]);
		}
		free(s);
	}
	return (expanded_str);
}
