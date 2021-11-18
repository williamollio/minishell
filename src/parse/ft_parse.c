#include "../../includes/minishell.h"

int	ft_parsing(char *line, t_parse **parse, t_env **env_head)
{
	*parse = NULL;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes or unspecified special characters", 2);
		return (EXIT_FAILURE);
	}
	ft_convert_dollar(parse, *env_head);
	ft_seperator(parse);
	ft_splitter(parse);
	ft_quotes(parse);
	return (EXIT_SUCCESS);
}
