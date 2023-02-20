/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zasabri <zasabri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 03:38:21 by abouramd          #+#    #+#             */
/*   Updated: 2023/02/20 03:55:26 by zasabri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"
#include "exec.h"

void child_signal(int sig)
{
    if (sig == SIGINT)
        exit (130);
}

void	cmd_exec(t_data *d,t_pipe *f)
{
    int i = fork();
    if (!i)
    {
    signal(SIGINT, child_signal);
    if (d->list_of_cmd->infile != 0)
    {
        if (d->list_of_cmd->infile < 0)
            ft_puterr(d->list_of_cmd->cmd[0], ": open fail", 1);
        else
            dup2(d->list_of_cmd->infile, 0);
    }   
    if (d->list_of_cmd->outfile != 1)
    {
        if (d->list_of_cmd->outfile < 0)
            ft_puterr(d->list_of_cmd->cmd[0], ": open fail", 1);
        else
            dup2(d->list_of_cmd->outfile, 1);
    }
	d->pathname = creat_path(d, f);
	if (execve(d->pathname, d->list_of_cmd->cmd, d->my_env) == -1)
		ft_puterr(d->list_of_cmd->cmd[0], strerror(errno), 1);
    }
    waitpid(i, NULL, 0);
}

int check_arg(char *s)
{
    size_t i = 0;
    if (s[i] == '-' && s[i] == '+')
        i++;
    while (s[i])
    {
        if (!ft_isdigit(s[i]))
            return 1;
        i++;
    }
    return 0;
}

void built_exit(t_data *f)
{
    ft_putendl_fd("exit", 1);
    if (f->list_of_cmd->cmd[1] != NULL)
    {
        if (f->list_of_cmd->cmd[2] == NULL && check_arg(f->list_of_cmd->cmd[1]) == 0)
        {
            exit(ft_atoi(f->list_of_cmd->cmd[1]));
        }
        else if (check_arg(f->list_of_cmd->cmd[1]) == 1)
        {
            ft_putendl_fd("minishell: exit: numeric argument required", 2);
            exit(255);
        }
        else
            ft_putendl_fd("minishell: exit: too many arguments", 2);
    }
    else
        exit(0);
}

void built_unset(t_data *f)
{   
    size_t i = 1;
    if (f->list_of_cmd->cmd[1] == NULL)
        ft_putendl_fd("unset: not enough arguments", 2);
    else
    {
        while(f->list_of_cmd->cmd[i])
            ft_env_rm(f->list_of_cmd->cmd[i++], &f->my_env);
    }
}

void built_pwd(t_data *f)
{
    char *pwd;
    if (f->list_of_cmd->cmd[1] != NULL)
    {
        printf("pwd: too many arguments\n");
    }
    else
    {
        pwd = malloc(UINT32_MAX);
        getcwd(pwd, UINT32_MAX);
        printf("%s\n", pwd);
        free(pwd);
    }
}

void built_env(t_data *f)
{
    size_t i = 0;

    while (f->my_env && f->my_env[i])
        ft_putendl_fd(f->my_env[i++], 1);
}

void built_export(t_data *f)
{
    size_t i = 1;

    if (f->list_of_cmd->cmd[1] == NULL)
        ft_putendl_fd("sort", 1);
    else
    {
        while (f->list_of_cmd->cmd[i])
            ft_env_add(f->list_of_cmd->cmd[i++], &f->my_env);
    }
}

void built_cd(t_data *f)
{
    char *pwd = malloc(UINT32_MAX);
    getcwd(pwd, UINT32_MAX);
    char *tmp = pwd;
    pwd = ft_strjoin("OLDPWD=", pwd);
    free(tmp);
    if (f->list_of_cmd->cmd[1] == NULL || !ft_strncmp(f->list_of_cmd->cmd[1], "~", 2))
    {
        char *p = ft_find_env("HOME", f->my_env);
        if (!p)
        ft_putendl_fd("minishell: cd: HOME not set", 2);
        else
        {
            if (chdir(p) < 0)
                perror("minishell: cd");
            else
              ft_env_add(pwd, &f->my_env);
        }
    }
    else
    {
        if (!ft_strncmp("-", f->list_of_cmd->cmd[1], 2))
        {
            char *p = ft_find_env("OLDPWD", f->my_env);
            if (!p)
                ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
            else
            {
                if (chdir(p) < 0)
                    perror("minishell: cd");   
                else
                {
                    ft_putendl_fd(p, 1);
                    ft_env_add(pwd, &f->my_env);
                }
                    
            }
        }
        else
        {
            if (chdir(f->list_of_cmd->cmd[1]) < 0)
                perror("minishell: cd");
            else
                ft_env_add(pwd, &f->my_env);
        }
            
    }
    free(pwd);
}

int ch_flag(char *s)
{
    size_t i = 0;
    
    if (s[i] != '-')
        return 0;
    i++;
    if (s[i] != 'n')
        return 0;
    while (s[i])
    {
        if (s[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

void built_echo(t_data *f)
{
    size_t i = 1;

    if (f->list_of_cmd->cmd[1] == NULL)
        ft_putendl_fd("", 1);
    else 
    {
        if (ch_flag(f->list_of_cmd->cmd[i]) == 1)
        {
            while (f->list_of_cmd->cmd[i] && ch_flag(f->list_of_cmd->cmd[i]) == 1)
                i++;
            while (f->list_of_cmd->cmd[i])
            {
                ft_putstr_fd(f->list_of_cmd->cmd[i], 1);
                i++;
                if (f->list_of_cmd->cmd[i] != NULL)
                    ft_putstr_fd(" ", 1);
            }
        }
        else
        {
            while (f->list_of_cmd->cmd[i])
            {
                ft_putstr_fd(f->list_of_cmd->cmd[i], 1);
                i++;
                if (f->list_of_cmd->cmd[i] != NULL)
                    ft_putstr_fd(" ", 1);
            }
            ft_putstr_fd("\n", 1);
        }
    }
}

int builtins(t_data *f)
{
    // printf("%s\n", f->list_of_cmd->cmd[0]);
    if (!ft_strncmp(f->list_of_cmd->cmd[0], "pwd", 4))
        return (built_pwd(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "cd", 3))
        return (built_cd(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "unset", 6))
        return (built_unset(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "export", 7))
        return(built_export(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "exit", 5))
        return(built_exit(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "echo", 5))
        return(built_echo(f), 1);
    else if (!ft_strncmp(f->list_of_cmd->cmd[0], "env", 4))
        return(built_env(f), 1);
    return 0;
}