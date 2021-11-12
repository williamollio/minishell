#include "../../includes/minishell.h"

char	*ft_get_next_str(char *line, int *i, int *quote_flag)
{
	char	*ret;
	int		x;

	ft_skip_space(line, i);
	x = (*i);
	while ((ft_operator_tool2(line, i) == 0 || (*quote_flag) == (-1)) && line[*i] != '\0')
	{
		if (line[*i] == '"' || ft_strncmp(&line[*i], "'", 1) == 0)
			(*quote_flag) *= (-1);
		(*i)++;
	}
	ret = ft_substr(line, x , (*i) - x);
	return (ret);
}

int	ft_lexer(char *line, t_parse **parse)
{
	int		i;
	int		op;
	int		loopflag;
	int		quote_flag;
	char	*str;

	quote_flag = 1;
	i = 0;
	loopflag = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '"' || ft_strncmp(&line[i], "'", 1) == 0)
			quote_flag *= (-1);
		ft_skip_space(line, &i);
		op = ft_operator_tool(line, &i);
		if ((op || loopflag == 0) && quote_flag == 1)
		{
			str = ft_get_next_str(line, &i, &quote_flag);
			ft_addback_parse(parse, str, op);
		}
		else
			i++;
		loopflag++;
	}
	return (quote_flag);
}
