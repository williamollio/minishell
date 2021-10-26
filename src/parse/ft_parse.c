#include "../../includes/minishell.h"

static int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

char **ft_line_path(char **envp, char **paths)
{
	int		x;
	char	*pathname;

	x = 0;
	while (envp[x] != NULL)
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'A'
		&& envp[x][2] == 'T' && envp[x][3] == 'H')
		{
			pathname = ft_substr(envp[x], 5, ft_strlen(envp[x]) - 5);
			paths = ft_split(pathname, ':');
			break ;
		}
		x++;
	}
	return (paths);
}

int	ft_is_builtin(char *s)
{
	if (ft_strncmp(s, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(s, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(s, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(s, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(s, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(s, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

int	check_commandpath(char **paths, char *cmd)
{
	int		i;
	char	*ret;
	char	*slash;
	int		rows;

	rows = countrows(paths);
	i = 0;
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		if (access(ret, F_OK) != -1)
		{
			ft_free1(slash);
			ft_free1(ret);
			return (1);
		}
		i++;
	}
	ft_free1(slash);
	ft_free1(ret);
	return (0);
}

void ft_parsing(char **envp, char *line, t_parse **parse)
{
	char	**arr;
	char	**paths = NULL;
	int		i;

	i = 0;
	paths = ft_line_path(envp, paths);
	arr = ft_split(line, ' ');
	while (arr[i])
	{
		if (ft_is_builtin(arr[i]))
		{
			ft_addback_parse(parse, arr[i], BUILT);

		}
		else if (check_commandpath(paths, arr[i]))
		{
			ft_addback_parse(parse, arr[i], SYS);
		}
		else
		{
			ft_operator(arr[i], parse);
		}
		i++;
	}
	ft_free2(paths);
	ft_get_list(*parse);
}