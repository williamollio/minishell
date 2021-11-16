#include "../../includes/minishell.h"

int	ft_nothing(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_next_str(char *line, int *i, int *quote_flag, int op, int *pipe_flag)
{
	char	*ret;
	int		x;

	ft_skip_space(line, i);
	x = (*i);
	while (line[*i] != '\0' && (ft_operator_tool2(line, i) == 0 || (*quote_flag) == (-1)))
	{
		if (line[*i] == '"' || ft_strncmp(&line[*i], "'", 1) == 0)
			(*quote_flag) *= (-1);
		(*i)++;
	}
	ret = ft_substr(line, x , (*i) - x);
	if (ft_nothing(ret) && op == 1)
		*pipe_flag = 1;
	return (ret);
}

int	ft_lexer(char *line, t_parse **parse)
{
	int		i;
	int		op;
	int		loopflag;
	int		quote_flag;
	char	*str;
	int		pipe_flag;

	pipe_flag = 0;
	quote_flag = 1;
	i = 0;
	loopflag = 0;
	while (line[i] != '\0')
	{
		// if (line[i] == '"' || ft_strncmp(&line[i], "'", 1) == 0) // for "e"cho case
		// 	quote_flag *= (-1);
		ft_skip_space(line, &i);
		op = ft_operator_tool(line, &i);
		if ((op || loopflag == 0) && quote_flag == 1)
		{
			str = ft_get_next_str(line, &i, &quote_flag, op, &pipe_flag);
			if (!ft_nothing(str))
				ft_addback_parse(parse, str, op, &pipe_flag);
			else
				free(str);
		}
		else
			i++;
		loopflag++;
	}
	return (quote_flag);
}
