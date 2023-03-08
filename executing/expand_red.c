/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_red.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouramd <abouramd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 17:53:47 by abouramd          #+#    #+#             */
/*   Updated: 2023/03/08 08:47:13 by abouramd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/exec.h"

static char	*fill_var(t_data *f, char *val, char *expanded_str)
{
	size_t	j;

	j = 0;
	if (!val)
		f->ambiguous = 1;
	if (val)
	{
		while (val && (val[j] == ' ' || val[j] == '\t'))
			j++;
		if (val && !val[j])
			f->ambiguous = 1;
		while (val[j] != ' ' && val[j] != '\t' && val[j] != '\0')
			j++;
		while (val && (val[j] == ' ' || val[j] == '\t'))
			j++;
		if (val && val[j])
			f->ambiguous = 1;
	}
	j = 0;
	while (val && val[j])
		expanded_str = add_str(expanded_str, val[j++]);
	return (expanded_str);
}

static char	*ft_replace_val(t_data *f, char *str, char *expanded_str,
		size_t *index)
{
	char	*val;
	char	*id;
	size_t	i;

	id = NULL;
	i = *index + 1;
	if (str && str[i] == '?')
	{
		val = ft_itoa(f->exit_status);
		expanded_str = fill_var(f, val, expanded_str);
		free(val);
		i++;
	}
	else if (str && !ft_isalnum(str[i]) && str[i] != '_')
		expanded_str = add_str(expanded_str, '$');
	else
	{
		while (str && (ft_isalnum(str[i]) || str[i] == '_'))
			id = add_str(id, str[i++]);
		expanded_str = fill_var(f, ft_find_env(id, f->my_env), expanded_str);
		free(id);
	}
	*index = i;
	return (expanded_str);
}

static char	*ft_split_expand(char *expanded_str)
{
	size_t	i;
	char	c;
	char	*tmp;

	c = 0;
	i = 0;
	tmp = NULL;
	while (expanded_str && (expanded_str[i] == ' ' || expanded_str[i] == '\t'))
		i++;
	while (expanded_str && expanded_str[i])
	{
		while (expanded_str && expanded_str[i])
		{
			if ((expanded_str[i] == '\t' || expanded_str[i] == ' ') && c == 0)
				break ;
			if ((expanded_str[i] == '\"' || expanded_str[i] == '\'') && c == 0)
				c = expanded_str[i];
			else if (c && expanded_str[i] == c)
				c = 0;
			else
				tmp = add_str(tmp, expanded_str[i]);
			i++;
		}
		while (expanded_str[i] == ' ' || expanded_str[i] == '\t')
			i++;
	}
	return (free(expanded_str), tmp);
}
// char	*ft_expand_in_here_doc(t_data *f, char *s, int type)
// {
// 	char	*expanded_str;
// 	size_t	i;

// 	if (type == 0)
// 		return (s);
// 	expanded_str = NULL;
// 	i = 0;
// 	if (s)
// 	{
// 		while (s && s[i])
// 		{
// 			if (s[i] == '$')
// 				expanded_str = ft_replace_val(f, s, expanded_str, &i);
// 			else
// 				expanded_str = add_str(expanded_str, s[i++]);
// 		}
// 		free(s);
// 	}
// 	return (expanded_str);
// }

// char	**ft_split_expand(char *expanded_str, char **tmp)
// {
// 	size_t	i;
// 	size_t	j;
// 	char	c;

// 	c = 0;
// 	i = 0;
// 	j = 0;
// 	while (expanded_str && expanded_str[i])
// 	{
// 		while ((expanded_str[i] == ' ' || expanded_str[i] == '\t')
// 			&& (expanded_str[i + 1] == ' ' || expanded_str[i + 1] == '\t'))
// 			i++;
// 		if ((expanded_str[i] == '\"' || expanded_str[i] == '\'') && c == 0)
// 			c = expanded_str[i];
// 		else if (c && expanded_str[i] == c)
// 			c = 0;
// 		else if (c == 0 && (expanded_str[i] == ' ' || expanded_str[i] == '\t'))
// 		{
// 			tmp = ft_ultimate_join(tmp, "");
// 			j++;
// 		}
// 		else
// 			tmp[j] = add_str(tmp[j], expanded_str[i]);
// 		i++;
// 	}
// 	free(expanded_str);
// 	return (tmp);
// }

// char	**ft_expand_str(t_data *f, char *s)
// {
// 	char	*expanded_str;
// 	size_t	i;
// 	char	c;
// 	char	**tmp;

// 	c = 0;
// 	i = 0;
// 	expanded_str = NULL;
// 	while (s && s[i])
// 	{
// 		if ((s[i] == '\"' || s[i] == '\'') && c == 0)
// 			c = s[i];
// 		else if (c && s[i] == c)
// 			c = 0;
// 		if (c != '\'' && s[i] == '$')
// 		{
// 			expanded_str = ft_replace_val(f, s, expanded_str, &i);
// 			continue ;
// 		}
// 		else
// 			expanded_str = add_str(expanded_str, s[i]);
// 		i++;
// 	}
// 	tmp = NULL;
// 	tmp = ft_ultimate_join(tmp, "");
// 	if (expanded_str)
// 		tmp = ft_split_expand(expanded_str, tmp);
// 	return (tmp);
// }

char	*ft_expand_in_red(t_data *f, char *s)
{
	char	*expanded_str;
	size_t	i;
	char	c;

	c = 0;
	i = 0;
	expanded_str = ft_strdup("");
	while (s && s[i])
	{
		if ((s[i] == '\"' || s[i] == '\'') && c == 0)
			c = s[i];
		else if (c && s[i] == c)
			c = 0;
		else if (c != '\'' && s[i] == '$')
		{
			expanded_str = ft_replace_val(f, s, expanded_str, &i);
			continue ;
		}
		else
			expanded_str = add_str(expanded_str, s[i]);
		i++;
	}
	expanded_str = ft_split_expand(expanded_str);
	return (expanded_str);
}
