#include "../../includes/minishell.h"

int ft_parsing(char *line, t_parse **parse, t_env_list **env_head)
{
	*parse = NULL;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes or unspecified special characters", 2);
		return (EXIT_FAILURE);
	}
	// printf("after lexer\n");
	// ft_print_list_parse_2(parse);
	ft_convert_dollar(parse, *env_head);

	ft_seperator(parse);

	t_parse 	*temp = *parse;

	while (temp != NULL)
	{
		temp = temp->next;
		if (temp == NULL)
			break ;
		if (temp->op == 1 && (temp->prev->op >= 2 && temp->prev->op <= 5))
			temp->op = 0;
	}

	ft_splitter(parse);

	ft_quotes(parse);
	return (EXIT_SUCCESS);
}
