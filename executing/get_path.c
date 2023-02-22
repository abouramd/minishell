#include "exec.h"


size_t count_size_of_path(char *s)
{
	size_t size = 0;
	size_t i = 0;

	if (s[i] != '\0')
	{
		if (s[i] == ':')
		{
			size += 2;
			size++;
			i++;
		}
		while(s[i])
		{
			if (s[i] == ':' && s[i - 1] == ':')
				size += 2;
			size++;
			i++;
		}
		if (s[i - 1] == ':')
			size += 2;
	}
	else
		size += 2;
    return size;
}

char *path_get(char *s)
{
	size_t i = 0;
	size_t n = 0;
	s = ft_strdup(s);
	
	char *p = malloc(count_size_of_path(s) + 1);
	if (s[n] != '\0')
	{
		if (s[n] == ':')
		{
			p[i++] = '.';
			p[i++] = '/';
			p[i++] = s[n++];
		}
		while(s[n])
		{
			if (s[n] == ':' && s[n - 1] == ':')
			{
				p[i++] = '.';
				p[i++] = '/';
			}
			p[i++] = s[n++];
		}
		if (s[n - 1] == ':')
		{
			p[i++] = '.';
			p[i++] = '/';
		}
	}
	else
	{
		p[i++] = '.';
		p[i++] = '/';
	}
	p[i] = '\0';
    return p;
}

char	**split_path(char **env)
{
	int		i;
	char	**s;
	char	*tmp;

	i = 0;
	s = NULL;
	while (env && env[i])
	{
		if (my_strstr(env[i], "PATH=") == 1)
		{
			tmp = path_get(&env[i][5]);
            // printf("%s\n", &env[i][5]);
            // printf("%s\n", tmp);
			s = ft_split(tmp, ':');
			break ;
		}
		i++;
	}
	return (s);
}