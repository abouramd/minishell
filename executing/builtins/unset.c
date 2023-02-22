#include "exec.h"

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