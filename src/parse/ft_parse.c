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

char *ft_remove_quotes(char *str)
{
	char	*ret;
	int		i;
	int		flag_single;
	int		flag_double;
	int		quote_count;

	i = 0;
	quote_count = 0;
	flag_single = 1;
	flag_double = 1;
	quote_count = 0;
	while (str[i])
	{
		if (str[i] == '"' && flag_single > 0)
		{
			flag_double *= (-1); // remember i where the quote is
			quote_count += 1;
		}
		else if (ft_strncmp(str[i] , "'", 1) == 0 && flag_double > 0)
		{
			flag_single *= (-1);
			quote_count += 1;
		}
		i++;
	}
	free(str);
	return (ret);
}

void ft_quotes(t_parse **parse)
{
	t_parse *tmp;
	int		i;

	tmp = *parse;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strnstr(tmp->cmd[i], "'", ft_strlen(tmp->cmd[i])) != 0 || ft_strchr(tmp->cmd[i], '"') != NULL)
				tmp->cmd[i] = ft_remove_quotes(tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
}

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

	ft_quotes(parse);

	return (EXIT_SUCCESS);
}
