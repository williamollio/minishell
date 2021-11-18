#include "../../includes/minishell.h"

void	ft_init_lexer(t_lexer *lex)
{
	lex->i = 0;
	lex->op = 0;
	lex->pipe_flag = 0;
	lex->quote_flag = 1;
	lex->loopflag = 0;
	lex->str = NULL;
}

int	ft_nothing(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_next_str(char *line, t_lexer *lex)
{
	char	*ret;
	int		x;

	if (lex->op == 4 || lex->op == 5)
		lex->i += 2;
	else if (lex->op)
		lex->i += 1;
	ft_skip_space(line, &lex->i);
	x = (lex->i);
	while (line[lex->i] != '\0' && (ft_operator_tool2(line, &lex->i) == 0
			|| (lex->quote_flag) == (-1)))
	{
		if (line[lex->i] == '"' || ft_strncmp(&line[lex->i], "'", 1) == 0)
			(lex->quote_flag) *= (-1);
		(lex->i)++;
	}
	ret = ft_substr(line, x, lex->i - x);
	if (ft_nothing(ret) && lex->op == 1)
		lex->pipe_flag = 1;
	return (ret);
}

int	ft_lexer(char *line, t_parse **parse)
{
	t_lexer	lex;

	ft_init_lexer(&lex);
	if (ft_strchr(line, '\\') != NULL || ft_strchr(line, ';'))
		return (-1);
	while (line[lex.i] != '\0')
	{
		ft_skip_space(line, &lex.i);
		lex.op = ft_operator_tool2(line, &lex.i);
		if ((lex.op || lex.loopflag == 0) && lex.quote_flag == 1)
		{
			lex.str = ft_get_next_str(line, &lex);
			if (!ft_nothing(lex.str))
				ft_addback_parse(parse, lex.str, lex.op, &lex.pipe_flag);
			else
				free(lex.str);
		}
		else
			lex.i++;
		lex.loopflag++;
	}
	return (lex.quote_flag);
}
