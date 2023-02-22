#include "exec.h"

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