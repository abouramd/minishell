/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_env_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 13:01:46 by zasabri           #+#    #+#             */
/*   Updated: 2023/02/25 14:31:24 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

char	*find_value(char *var, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (env[i])
	{
		//printf("[%s]\n", env[i]);
		if (!(ft_strncmp(env[i], var, ft_strlen(var))))
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

char	*print_env_content(t_cmd_list *cmd_table, char **env)
{
	t_cmd_list	*tmp;
	char		*value;

	tmp = cmd_table;
	value = NULL;
	int i = 0;
	while (tmp->cmd[i] != NULL)
	{
		if (ft_strnstr(tmp->cmd[i], "$", 1))
		{
			//printf("--->%s\n", tmp->cmd[i] + 1);
			if (tmp->cmd[i])
			{
				value = find_value(tmp->cmd[i] + 1, env);
				break;
			}
		}
		i++;
	}
	//printf("%s\n", value);
	return (value);
}