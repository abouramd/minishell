#include "exec.h"

char **sort_env(char **s)
{
    size_t i = 0;
    size_t j = 0;
    char **a = NULL;
    char **b = NULL;

    while(s && s[j])
    {
        i = 0;
        a = ft_split(s[j],'=');
        while (i < j)
        {
            b = ft_split(s[i],'=');
            if (ft_strncmp(a[0], b[0], ft_strlen(b[0]) + 1) <= 0)
            {
                char *tmp = s[j];
                s[j] = s[i];
                s[i] = tmp;
            }
            ft_free(b);
            i++;
        }
        ft_free(a);
        j++;
    }
    return s;
}
void print_sort(char **s)
{
    size_t i = 0;
    sort_env(s);
    while (s[i])
    {
        ft_putstr_fd("declare -x ", 1);
        size_t h = 0;
        while (s[i][h] && s[i][h] != '=')
            ft_putchar_fd(s[i][h++], 1);
        if (s[i][h] == '=')
        {
            ft_putchar_fd(s[i][h++], 1);
            ft_putchar_fd('\"', 1);
            while (s[i][h] && s[i][h] != '=')
                ft_putchar_fd(s[i][h++], 1);
            ft_putchar_fd('\"', 1);
        }
        ft_putchar_fd('\n', 1);
        i++;
    }
}

// int main()
// {
//     char **s = ft_split("^TERM_PROGRAM=iTerm.app^a^b^A^TERM=xterm-256color^SHELL=/bin/zsh^TMPDIR=/var/folders/zz/zyxvpxvq6csfxvn_n0000knr0004nf/T/^Apple_PubSub_Socket_Render=/private/tmp/com.apple.launchd.U7lP3GY7DN/Render^TERM_PROGRAM_VERSION=3.4.16^TERM_SESSION_ID=w0t0p0:1A16B0DF-586A-46AB-936F-638EE3FA75AD^ZSH=/Users/abouramd/.oh-my-zsh^USER=abouramd^COMMAND_MODE=unix2003^SSH_AUTH_SOCK=/private/tmp/com.apple.launchd.SypIfK9B1A/Listeners^__CF_USER_TEXT_ENCODING=0x0:0:0^PAGER=less^LSCOLORS=Gxfxcxdxbxegedabagacad^PATH=/Users/abouramd/goinfre/homebrew/bin:/Users/abouramd/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Frameworks/Mono.framework/Versions/Current/Commands^PWD=/Users/abouramd/Desktop/work_dir/mini_back/minishell03^LANG=en_US.UTF-8^ITERM_PROFILE=Default^XPC_FLAGS=0x0^XPC_SERVICE_NAME=0^SHLVL=2^HOME=/Users/abouramd^COLORFGBG=7;0^LC_TERMINAL_VERSION=3.4.16^ITERM_SESSION_ID=w0t0p0:1A16B0DF-586A-46AB-936F-638EE3FA75AD^LESS=-R^LOGNAME=abouramd^LC_TERMINAL=iTerm2^SECURITYSESSIONID=186a8^COLORTERM=truecolor^_=/usr/bin/env" , '^');
//     print_sort(s);
// }
