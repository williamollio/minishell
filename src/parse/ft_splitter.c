#include "../../includes/minishell.h"

void	ft_command_type(t_parse **parse)
{
	t_parse	*temp;

	temp = *parse;
	while (temp != NULL)
	{
		temp = temp->next;
		if (temp == NULL)
			break ;
		if (temp->op == 1 && (temp->prev->op >= 2 && temp->prev->op <= 5))
			temp->op = 0;
	}
}

void	ft_splitter(t_parse **parse)
{
	t_parse	*temp;
	int		count;

	ft_command_type(parse);
	temp = *parse;
	while (temp != NULL)
	{
		if (temp->cmd == NULL)
		{
			temp->cmd = ft_split2(temp->str, ' ', &count);
			ft_free1(temp->str);
		}
		temp = temp->next;
	}
}
