/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:59:21 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/14 08:32:32 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int isValid(char * s){
    char *m = malloc(ft_strlen(s));
    int t = 0, k = 0, l = 0;
    for (int i = 0;s[i];i++)
    {
        if (ft_strchr("({[", s[i]))
        {
            if (s[i] == '(')
            m[t] = ')';
            if (s[i] == '{')
            m[t] = '}';
            if (s[i] == '[')
            m[t] = ']';
            t++;
        }
        // if (ft_strchr("\"\'", s[i]))
        // {
        //     if (s[i] == '\"' && l == 0)
        //     {
        //         m[t] = '\"';
        //         l = 1;
        //         t++;
        //     }
        //     if (s[i] == '\'' && k == 0)
        //     {
        //         m[t] = '\'';
        //         k = 1;
        //         t++;
        //     }
        //     if (s[i] == '\"' && l == 1)
        //     {
        //         m[t] = '     ';
        //         l = 1;
        //         t++;
        //     }
        //     if (s[i] == '\'' && k == 1)
        //     {
        //         m[t] = '\'';
        //         k = 1;
        //         t++;
        //     }
        // }
        if (ft_strchr("]})", s[i]))
        {
            if (t == 0)
			{
                return 0;
				free(m);
			}
            t--;
            if (m[t] != s[i])
			{
                return 0;
				free(m);
			}
            m[t] = 0;
        }
    }
    if (t != 0)
    {
        return 0;
		free(m);
	}
    free(m);
    return 1;
}

// char	*parse_str(char	*str)
// {
// 	char *save;
// 	int	i = 0
	
// 	save = NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == "\"")
// 		{
// 			i+=1;
// 			while (str[i] && str[i] != '\"')
// 			{
// 				save = add_str(save, str[i]);
// 				i++;
// 			}
// 			if (str[i] == '\0')
// 				return (NULL);
// 			i+=1;
// 		}
// 	}
// }