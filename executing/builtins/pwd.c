#include "exec.h"

void built_pwd(t_data *f)
{
    char *pwd;
    if (f->list_of_cmd->cmd[1] != NULL)
    {
        ft_putendl_fd("pwd: too many arguments", 2);
    }
    else
    {
        pwd = malloc(UINT32_MAX);
        getcwd(pwd, UINT32_MAX);
        ft_putendl_fd(pwd, 1);
        free(pwd);
    }
}