#include "../../includes/minishell.h"

// char **ft_line_path(char **envp)
// {
// 	int		x;
// 	char	*pathname;
// 	char	**paths;

// 	paths = NULL;
// 	x = 0;
// 	while (envp[x] != NULL)
// 	{
// 		if (envp[x][0] == 'P' && envp[x][1] == 'A'
// 		&& envp[x][2] == 'T' && envp[x][3] == 'H')
// 		{
// 			pathname = ft_substr(envp[x], 5, ft_strlen(envp[x]) - 5);
// 			paths = ft_split(pathname, ':');
// 			break ;
// 		}
// 		x++;
// 	}
// 	ft_get_paths(paths);
// 	return (paths);
// }

int ft_parsing(char **envp, char *line, t_parse **parse, t_env_list **env_head)
{
	*parse = NULL;

	(void)envp;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes", 2);
		// return error here
	}

	ft_convert_dollar(parse, *env_head);

	// printf("1: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");

	ft_seperator(parse);

	// printf("2: -------------------------\n");
	// ft_print_list_parse_2(parse);
	// printf("----------------------------\n\n\n\n\n");

	ft_splitter(parse);

	return (EXIT_SUCCESS);
}
