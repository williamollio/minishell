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
	int		y;
	int		op;
	char	*str;

	(void)envp;
	*parse = NULL;
	i = 0;
	y = 0;
	while (line[i] != '\0')
	{
		op = ft_operator_tool2(line, &i);
		if (op || line[i + 1] == '\0')
		{
			if (line[i + 1] == '\0')
				i++;
			str = ft_substr(line, y, i - y);
			ft_addback_parse(parse, str, op);
			y = i;
			if (line[i] == '\0')
				break ;
			if (op == 4 || op == 5)
				i++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}


// access