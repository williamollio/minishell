#include "../../includes/minishell.h"

void	ft_splitter(t_parse **parse)
{
	t_parse	*temp;
	int		count;

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
