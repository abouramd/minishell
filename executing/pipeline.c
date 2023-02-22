#include "exec.h"

void	run_cmd(t_data *d,t_pipe *f)
{
    sigaction(SIGINT, &d->old_sigint, NULL);
    sigaction(SIGQUIT, &d->old_sigquit, NULL);
    tcsetattr(0, TCSANOW, &d->old_tty);
    char *cmd;
    if (d->list_of_cmd->cmd)
        cmd = d->list_of_cmd->cmd[0];
    else
        cmd = "minishell";
    
    if (d->list_of_cmd->infile != 0)
    {
        if (d->list_of_cmd->infile < 0)
            ft_puterr(cmd, ": open fail in infile", 1);
        else
        {
            dup2(d->list_of_cmd->infile, 0);
            close(d->list_of_cmd->infile);
        }
    }   
    if (d->list_of_cmd->outfile != 1)
    {
        if (d->list_of_cmd->outfile < 0)
            ft_puterr(cmd, ": open fail in outfile", 1);
        else
        {
            dup2(d->list_of_cmd->outfile, 1);
            close(d->list_of_cmd->outfile);
        }
    }
    if (d->list_of_cmd->cmd)
    {
	    d->pathname = creat_path(d, f);
	    if (execve(d->pathname, d->list_of_cmd->cmd, d->my_env) == -1)
		    ft_puterr(d->list_of_cmd->cmd[0], strerror(errno), 1);
    }
}
void give_fd(t_cmd_list *f, int infile, int outfile)
{
    if (f->infile == 0)
        f->infile = infile;
    else if (infile != 0)
        close(infile);

    if (f->outfile == 1)
        f->outfile = outfile;
    else if (outfile != 1)
        close(outfile);
    // printf("f->outfile => %d\n", f->outfile);
    // printf("f->infile => %d\n", f->infile);
}

int creat_child(t_data *d, t_pipe *f, int pfd)
{
	int		id;
	
	id = fork();
	if (id == -1)
		ft_putendl_fd(strerror(errno), 2);
    else if (id == 0)
    {
        if (pfd != 0)
            close (pfd);
        t_cmd_list *tmp = d->list_of_cmd->next;
        while (tmp)
        {
            if (tmp->infile != 0)
            {
                close(tmp->infile);
                tmp->infile = 0;
            }
            if (tmp->outfile != 1)
            {
                close(tmp->outfile);
                tmp->outfile = 1;
            }
            tmp = tmp->next;
        }
        if (!builtins(d))
            run_cmd(d, f);
        else
            exit(d->exit_status);
    }
    else {
        if (d->list_of_cmd->infile != 0)
        {
            close(d->list_of_cmd->infile);
            d->list_of_cmd->infile = 0;
        }
        if (d->list_of_cmd->outfile != 1)
        {
            close(d->list_of_cmd->outfile);
            d->list_of_cmd->outfile = 1;
        }
    }
	return id;
}

void	pipeline(t_data *d, t_pipe *f)
{
    t_cmd_list *tmp;
    int fd[2];
    int infile = 0;
    int outfile = 1;
    int id;
    
    if (d->list_of_cmd->next != NULL || !builtins(d))
    {
        tmp = d->list_of_cmd;
        while(d->list_of_cmd)
        {
            fd[0] = 0;
            fd[1] = 1;
            if (d->list_of_cmd->next)
                pipe(fd);
            outfile = fd[1];
            give_fd(d->list_of_cmd, infile, outfile);
            id = creat_child(d, f, fd[0]);
            d->list_of_cmd = d->list_of_cmd->next;
            infile = fd[0];
        }
        d->list_of_cmd = tmp;
        waitpid(id, &d->exit_status, 0);
        if (WIFSIGNALED(d->exit_status))
            d->exit_status = 128 + WEXITSTATUS(d->exit_status);
        else
            d->exit_status = WEXITSTATUS(d->exit_status);
        while(wait(NULL) != -1);
    }
}