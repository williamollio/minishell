#include "../../includes/minishell.h"

static void ft_init_quotes(t_quotes *quotes)
{
	quotes->i = 0;
	quotes->x = 0;
	quotes->i1 = 0;
	quotes->i2 = 0;
	quotes->pos1 = 0;
	quotes->flag_single = 1;
	quotes->flag_double = 1;
	quotes->temp1 = NULL;
	quotes->temp2 = NULL;
	quotes->temp3 = NULL;
	quotes->temp4 = NULL;
	quotes->temp5 = NULL;
}

char *ft_remove_quotes(char *str)
{
	t_quotes	quotes;

	ft_init_quotes(&quotes);
	while (str[quotes.i])
	{
		if (str[quotes.i] == '"')
		{
			quotes.i2 = quotes.i;
			quotes.i++;
			quotes.x = 0;
			while (str[quotes.i] && str[quotes.i] != '"')
			{
				quotes.i++;
				quotes.x++;
			}
			quotes.temp1 = ft_substr(str, quotes.i1, quotes.i2 - quotes.i1);
			if (quotes.temp4 != NULL)
			{
				quotes.temp5 = ft_strjoin(quotes.temp3, quotes.temp1);
				free(quotes.temp1);
				free(quotes.temp3);
				free(quotes.temp4);
				quotes.temp1 = quotes.temp5;
				free(quotes.temp5);
			}
			quotes.temp2 = ft_substr(str, quotes.i2 + 1, quotes.x);
			quotes.temp3 = ft_strjoin(quotes.temp1, quotes.temp2);
			free(quotes.temp1);
			free(quotes.temp2);
			quotes.temp4 = ft_strjoin(quotes.temp3, &str[quotes.i + 1]);
			quotes.i1 = quotes.i + 1;
		}
		quotes.i++;
	}
	free(quotes.temp3);
	free(str);
	return (quotes.temp4);
}

void ft_quotes(t_parse **parse)
{
	t_parse	*tmp;
	int		i;

	tmp = *parse;
	while (tmp != NULL)
	{
		i = 0;
		while (tmp->cmd[i])
		{
			if (ft_strnstr(tmp->cmd[i], "'", ft_strlen(tmp->cmd[i])) != 0
				|| ft_strchr(tmp->cmd[i], '"') != NULL)
				tmp->cmd[i] = ft_remove_quotes(tmp->cmd[i]);
			i++;
		}
		tmp = tmp->next;
	}
}