#include "../../includes/minishell.h"

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

	ft_splitter(parse);

	ft_quotes(parse);

	return (EXIT_SUCCESS);
}
