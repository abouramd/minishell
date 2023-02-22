#include "exec.h"


void built_export(t_data *f)
{
    size_t i = 1;

    if (f->list_of_cmd->cmd[1] == NULL)
    {
        char **en = alloc_env(f->my_env);
        print_sort(en);
        ft_free(en);
    }
    else
    {
        while (f->list_of_cmd->cmd[i])
            ft_env_add(f->list_of_cmd->cmd[i++], &f->my_env);
    }
}