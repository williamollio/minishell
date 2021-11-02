#include "../../includes/minishell.h"

static int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

char **ft_line_path(char **envp)
{
	int		x;
	char	*pathname;
	char	**paths;

	paths = NULL;
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
	ft_get_paths(paths);
	return (paths);
}

int	ft_is_builtin(char *s)
{
	if (ft_strncmp(s, "echo", 4) == 0 && ft_strlen(s) == 4)
		return (1);
	else if (ft_strncmp(s, "pwd", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	else if (ft_strncmp(s, "cd", 2) == 0 && ft_strlen(s) == 2)
		return (1);
	else if (ft_strncmp(s, "export", 6) == 0 && ft_strlen(s) == 6)
		return (1);
	else if (ft_strncmp(s, "unset", 5) == 0 && ft_strlen(s) == 5)
		return (1);
	else if (ft_strncmp(s, "env", 3) == 0 && ft_strlen(s) == 3)
		return (1);
	else if (ft_strncmp(s, "exit", 4) == 0 && ft_strlen(s) == 4)
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

char **ft_parsing(char **envp, char *line, t_parse **parse)
{
	char	**arr;
	char	**paths;
	int		i;

	i = 0;
	paths = ft_line_path(envp);
	arr = ft_split(line, ' ');
	if (ft_first(paths, i, parse, arr))
		return (arr);
	while (arr[i])
	{
		if (ft_is_builtin(arr[i]))
		{
			ft_addback_parse(parse, arr[i], BUILT);
			ft_cmd(&i, parse, arr);
			ft_print_list_parse(parse);
		}
		else if (check_commandpath(paths, arr[i]))
		{
			ft_addback_parse(parse, arr[i], SYS);
			ft_cmd(&i, parse, arr);
		}
		else
		{
			ft_arg(&i, parse, arr);
			if (ft_operator(i, parse, arr))
			{
				printf("shit\n");
				break;
			}
		}
		i++;
	}
	ft_free2(paths);
	ft_get_list(*parse);
	return (arr);
}
