/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/14 07:59:21 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/18 02:16:04 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// int isValid(char * s){
//     char *m = malloc(ft_strlen(s));
//     int t = 0, k = 0, l = 0;
//     for (int i = 0;s[i];i++)
//     {
//         if (ft_strchr("({[", s[i]))
//         {
//             if (s[i] == '(')
//             m[t] = ')';
//             if (s[i] == '{')
//             m[t] = '}';
//             if (s[i] == '[')
//             m[t] = ']';
//             t++;
//         }
//         if (ft_strchr("\"\'", s[i]))
//         {
//             if (s[i] == '\"' && l == 0)
//             {
//                 m[t] = '\"';
//                 l = 1;
//                 t++;
//             }
//             if (s[i] == '\'' && k == 0)
//             {
//                 m[t] = '\'';
//                 k = 1;
//                 t++;
//             }
//             if (s[i] == '\"' && l == 1)
//             {
//                 m[t] = '     ';
//                 l = 1;
//                 t++;
//             }
//             if (s[i] == '\'' && k == 1)
//             {
//                 m[t] = '\'';
//                 k = 1;
//                 t++;
//             }
//         }
//         if (ft_strchr("]})", s[i]))
//         {
//             if (t == 0)
// 			{
//                 return 0;
// 				free(m);
// 			}
//             t--;
//             if (m[t] != s[i])
// 			{
//                 return 0;
// 				free(m);
// 			}
//             m[t] = 0;
//         }
//     }
//     if (t != 0)
//     {
//         return 0;
// 		free(m);
// 	}
//     free(m);
//     return 1;
// }

char	*check_str(char *str)
{
	char	*new_str;
    int     i;

    new_str = NULL;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
		{	
			i++;
			while (str[i] && str[i] != '\'')
			{
				new_str = add_str(new_str, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else if (str[i] == '\"')
		{
			i += 1;
			while (str[i] && str[i] != '\"')
			{
				new_str = add_str(new_str, str[i]);
				i++;
			}
			if (str[i] == '\0')
				return (NULL);
			i++;
		}
		else
		{
			new_str = add_str(new_str, str[i]);
			i++;
		}
	}
	return (new_str);
}