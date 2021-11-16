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



	ft_seperator(parse);



	t_parse 	*temp = *parse;

	while (temp != NULL)
	{
		temp = temp->next;
		if (temp == NULL)
			break ;
		if (temp->op == 1 && (temp->prev->op >= 2 && temp->prev->op <= 5))
		{
			temp->op = 0;
			// temp->pipe_flag = 1;
		}
	}

	ft_splitter(parse);

	return (EXIT_SUCCESS);
}
