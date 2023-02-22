#include "exec.h"

void go_to_home(t_data *f, char *oldpwd)
{
    char *p;
    
    p = ft_find_env("HOME", f->my_env);
    if (!p)
    {
        ft_putendl_fd("minishell: cd: HOME not set", 2);
        f->exit_status = 1;
    }
    else
    {
        if (chdir(p) < 0)
        {
            perror("minishell: cd");
            f->exit_status = 1;
        }
        else
          ft_env_add(oldpwd, &f->my_env);
    }
}

void go_to_oldpwd(t_data *f, char *oldpwd)
{
    char *p;
    
    p = ft_find_env("OLDPWD", f->my_env);
    if (!p)
    {
        ft_putendl_fd("minishell: cd: OLDPWD not set", 2);
        f->exit_status = 1;
    }
    else
    {
        if (chdir(p) < 0)
        {
            perror("minishell: cd");   
            f->exit_status = 1;
        }
        else
        {
            ft_putendl_fd(p, f->list_of_cmd->outfile);
            ft_env_add(oldpwd, &f->my_env);
        }
            
    }
}

void go_to_dir(t_data *f, char *oldpwd)
{
    if (chdir(f->list_of_cmd->cmd[1]) < 0)
    {
        perror("minishell: cd");
        f->exit_status = 1;
    }
    else
        ft_env_add(oldpwd, &f->my_env);
}

void built_cd(t_data *f)
{
    char *pwd;
    char *tmp;
    
    pwd = malloc(PATH_MAX);
    getcwd(pwd, PATH_MAX);
    tmp = pwd;
    pwd = ft_strjoin("OLDPWD=", pwd);
    free(tmp);
    if (f->list_of_cmd->cmd[1] == NULL || !ft_strncmp(f->list_of_cmd->cmd[1], "~", 2))
        go_to_home(f,pwd);
    else
    {
        if (!ft_strncmp("-", f->list_of_cmd->cmd[1], 2))
            go_to_oldpwd(f,pwd);
        else
            go_to_dir(f,pwd);
    }
    free(pwd);
}
