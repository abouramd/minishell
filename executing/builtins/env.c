#include "exec.h"

void built_env(t_data *f)
{
    size_t i = 0;

    while (f->my_env && f->my_env[i])
    {
        if (ft_strchr(f->my_env[i], '='))
            ft_putendl_fd(f->my_env[i], f->list_of_cmd->outfile);
        i++;
    }
}