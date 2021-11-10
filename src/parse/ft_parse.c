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
	ft_get_paths(paths);
	return (paths);
}

int ft_parsing(char **envp, char *line, t_parse **parse)
{
	int		i;
	char	**paths;

	*parse = NULL;
	i = 0;
	paths = ft_line_path(envp);
	while (line[i] != '\0')
	{
		ft_bef(parse, line, &i);
		if (!ft_caller_builtin(parse, line, &i))
			printf("builtin found\n");
		else if (!ft_caller_sys_fct(parse, paths, line, &i))
			printf("sys function found\n");
		ft_after(parse, line, &i);
		// ft_print_last(parse);
		// printf("&line[i]:%s$\n", &line[i]);
		if (line[i] == '\0')
			break;
		//i++;
	}
	ft_free2(paths);
	ft_get_list(*parse);
	return (EXIT_SUCCESS);
}


// access