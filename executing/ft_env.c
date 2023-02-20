#include "exec.h"

char**    realloc_env(char **old_env, char *str)
{
    char *tmp;
    char h[2]={127, 0};
    
    size_t i = 0;
    while (old_env[i])
        i++;
    str = ft_strjoin(h, str);
    while (i > 0)
    {
        tmp = str;
        str = ft_strjoin(old_env[i - 1], str);
        free(tmp);
        tmp = str;
        str = ft_strjoin(h, str);
        free(tmp);
        i--;
    }
    ft_free(old_env);
    return (ft_split(str, 127));
}

void ft_env_rm(char *elem, char ***env)
{
    char **my_env = *env;
    char **s;
    char *tmp;
    size_t index = 0;

    while(my_env && my_env[index])
    {
        s = ft_split(my_env[index], '=');
        if(!ft_strncmp(s[0], elem, ft_strlen(elem) + 1))
        {
            tmp = ft_strdup("");
            if (!tmp)
                exit(1);
            free(my_env[index]);
            my_env[index] = tmp;
            *env = realloc_env(my_env, "");
            ft_free(s);
            break ;
        }
        ft_free(s);
        index++;
    }
}

char *ft_find_env(char *elem, char **my_env)
{
    char **s;
    size_t index = 0;

    while(my_env && my_env[index])
    {
        s = ft_split(my_env[index], '=');
        if(!ft_strncmp(s[0], elem, ft_strlen(elem) + 1))
        {
            ft_free(s);
            return (ft_strchr(my_env[index], '=') + 1);
        }
        ft_free(s);
        index++;
    }
    return NULL;
}

void ft_env_add(char *elem, char ***env)
{
    char **my_env = *env;
    char **s;
    char **t;
    char *tmp;
    size_t index = 0;

    t = ft_split(elem, '=');
    while(my_env && my_env[index])
    {
        s = ft_split(my_env[index], '=');
        if(!ft_strncmp(s[0], t[0], ft_strlen(t[0]) + 1))
        {
            tmp = ft_strdup(elem);
            if (!tmp)
                exit(1);
            free(my_env[index]);
            my_env[index] = tmp;
            ft_free(s);
            ft_free(t);
            return ;
        }
        ft_free(s);
        index++;
    }
    *env = realloc_env(my_env, elem);
    ft_free(t);
}