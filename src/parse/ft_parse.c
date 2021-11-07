#include "../../includes/minishell.h"

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
	return (paths);
}

int ft_parsing(char **envp, char *line, t_parse **parse)
{
	int		i;
	char	**paths;

	i = 0;
	paths = ft_line_path(envp);
	while (line[i])
	{
		ft_space_bef(parse, line, &i);
		if (!ft_caller_builtin(parse, line, &i))
			printf("builtin found\n");
		else if (!ft_caller_sys_fct(parse, paths, line, &i))
			printf("sys function found\n");
		//printf("line[i] %c\n", line[i]);
		ft_space_after(parse, line, &i);
		//i++;
	}
	ft_free2(paths);
	ft_get_list(*parse);
	return (EXIT_SUCCESS);
}
