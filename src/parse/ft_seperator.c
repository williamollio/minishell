#include "../../includes/minishell.h"

char	**ft_create_cmd(char **split, int count)
{
	int	s;
	int	i;
	char	**cmd;

	s = 1;
	i = 0;
	cmd = malloc(sizeof(char *) * (count + 1));
	while (split[s])
	{
		cmd[i] = ft_strdup(split[s]);
		i++;
		s++;
	}
	cmd[i] = NULL;
	return (cmd);
}

void	ft_flip_nodes(t_parse **parse, t_parse *temp)
{
	if (*parse == temp->prev)
	{
		temp->prev->next = temp->next;
		temp->next = temp->prev;
		*parse = temp;
	}
	else // dont know if its working
	{
		temp->prev->next = temp->next;
		temp->next = temp->prev;
		temp->prev->prev->next = temp;
	}
}

int ft_special(t_parse **parse, char **split, t_parse *temp)
{
	char	*str;
	int		i;

	if (split[1] != NULL && *parse != temp  && (temp->prev->op == CMD || temp->prev->op == PIPE))
	{
		str = ft_strdup(temp->prev->str);
		free(temp->prev->str);
		i = 1;
		while (split[i])
		{
			ft_append(&str, &split[i]);
			i++;
		}
		temp->prev->str = str;
		ft_flip_nodes(parse, temp);
		return (0); // case : cmd <in arg
	}
	return (1); // case : <in cmd arg
}

void	ft_seperator(t_parse **parse)
{
	t_parse *temp;
	char	**split;
	char	**cmd;
	int		count = 0;

	temp = *parse;
	while (temp != NULL)
	{
		if (temp->op >= 2 && temp->op <= 5)
		{
			split = ft_split2(temp->str, ' ', &count);
			ft_free1(temp->str);
			temp->str = ft_strdup(split[0]);
			if (split[1] != NULL && ft_special(parse, split, temp))
			{
				cmd = ft_create_cmd(split, count);
				ft_add_next(parse, temp, cmd, CMD);
			}
			ft_free2(split);
		}
		temp = temp->next;
	}
}