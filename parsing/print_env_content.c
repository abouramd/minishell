/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:01:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/25 17:45:22 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*find_value(char *var, char **env)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (env[i])
	{
		//printf("[%s]\n", env[i]);
		k = 0;
		while (env[i][k] && env[i][k] != '=')
			k++;
		if (!(ft_strncmp(env[i], var, k)) && ft_strlen(var) == (size_t)k)
		{
			//printf("==>%s\n", env[i]);
			j = ft_strlen(env[i]) - 1;
			while (env[i][j] != '=')
				j--;
			return (&env[i][j + 1]);	
		}
		i++;
	}
	return (NULL);
}
char	*take_care_of_dollar_sign(char	*line)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == '$' && ft_isalpha(line[i + 1]))
			j++;
		i++;
	}
	str = malloc(i + j + 1);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (i != 0 && (line[i] == '$' && ft_isalpha(line[i - 1])))
		{
			str[j] = ' ';
			j++;
		}
		str[j] = line[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
char	*print_env_content(char	*line, char **env)
{
	// t_cmd_list	*tmp;
	// char		*value;

	// tmp = cmd_table;
	// value = NULL;
	//env = NULL;
	// int i = 0;
	// while (tmp->cmd[i] != NULL)
	// {
	// 	if (!(ft_strnstr(tmp->cmd[i], "$", 1)))
	// 		return (NULL);
	// 	else if (ft_strnstr(tmp->cmd[i], "$", 1))
	// 	{
	// 		if (tmp->cmd[i][1] == '$')
	// 			printf("57162");
	// 		if (tmp->cmd[i])
	// 		{
	// 			value = find_value(tmp->cmd[i] + 1, env);
	// 			break;
	// 		}
	// 	}
	// 	i++;
	// }
	// if (value)
	// 	printf("%s\n", value);
	// else
	// 	printf("\n");
	// return (value);
	char	**str;
	char	*good_line;
	char	*save = NULL;
	int		i;
	//int		j;

	i = 0;
	// printf("[%s]\n", take_care_of_dollar_sign(line));
	// return (NULL);
	good_line = take_care_of_dollar_sign(line);
	str = ft_split(good_line, ' ');
	while (str[i])
	{
		//printf("[%s]\n", str[i++]);
		if (ft_strnstr(str[i], "$", 1) && ft_isalpha(str[i][1]))
			save = find_value(str[i] + 1, env);
		if (save)
			printf("%s\n", save);
		else
			printf("\n");
		i++;
	}
	return (save);
}