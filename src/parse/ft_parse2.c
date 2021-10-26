#include "../../includes/minishell.h"

int ft_operator(char *str, t_parse **parse)
{
	//t_parse	*last;

	if (ft_strchr(str, '|') != NULL)
	{
		//printf("%s\n", ft_strchr(str, '|'));
		ft_get_last(parse)->op = 1;
	}
	return(1);
}