#include "../../includes/minishell.h"

/* NEW PARSING */

void ft_append(char **last_arg, char **arg)
{
	char	*temp;

	if (ft_strncmp(*last_arg, "", 1) == 0)
		*last_arg = *arg;
	else
	{
		temp = ft_strjoin(*last_arg, "");
		ft_free1(*last_arg);
		*last_arg = temp;
		temp = ft_strjoin(*last_arg, *arg);
		ft_free1(*last_arg);
		*last_arg = temp;
	}
}

void ft_arg_tool(t_parse *last, char *line, int *x)
{
	int		i;
	int		y;
	char	*arg;

	i = 1;
	y = *x;
	while (line[*x] && line[*x] != ' ' && ft_operator_tool(line, x) == 0)
	{
		i++;
		*x += 1;
		if (line[*x] == '-')
			break;
	}
	arg = ft_substr(line, y, i);
	ft_append(&last->arg, &arg);
}


void ft_arg(t_parse **parse, char *line, int *x)
{
	t_parse	*last;

	last = NULL;
	if (*parse != NULL)
	{
		last = ft_get_last(parse);
		if (last->cmd && line[*x] == '-')
			ft_arg_tool(last, line, x);
		else if (ft_strncmp(last->cmd, "", 1) == 0 && line[*x] == '-')
			ft_arg_error(last, parse, x, line);
	}
	else if (line[*x] == '-')
		ft_arg_error(last, parse, x, line);
}

void ft_str_tool(t_parse *last, char *line, int *x)
{
	int		i;
	int		y;
	char	*str;

	i = 1;
	y = *x;
	while (line[*x] && line[*x] != ' ' && ft_operator_tool(line, x) == 0)
	{
		i++;
		*x += 1;
	}
	str = ft_substr(line, y, i);
	ft_append(&last->str, &str);
}

void ft_arg_error(t_parse *last, t_parse **parse, int *x, char *line)
{
	int		i;
	int		y;
	char	*arg;

	i = 1;
	y = *x;
	if (*parse == NULL || ft_strncmp(last->cmd, "", 1) == 0)
	{
		while (line[*x] && line[*x] != ' ' && ft_operator_tool(line, x) == 0)
		{
			i++;
			*x += 1;
			if (line[*x] == '-')
				break;
		}
		arg = ft_substr(line, y, i);
		ft_addback_parse(parse, arg, SYS);
	}
}

void ft_str_error(t_parse *last, t_parse **parse, int *x, char *line)
{
	int	i;
	int y;
	char *str;

	i = 1;
	y = *x;
	printf("last->cmd : %s\n", last->cmd);
	if (*parse == NULL || ft_strncmp(last->cmd, "", 1) == 0)
	{
		while (line[*x] && line[*x] != ' ' && ft_operator_tool(line, x) == 0)
		{
			i++;
			*x += 1;
		}
		str = ft_substr(line, y, i);
		ft_addback_parse(parse, str, SYS);
	}
}

void ft_str(t_parse **parse, char *line, int *x)
{
	t_parse	*last;
	int		y;
	char	**paths;

	paths = ft_get_paths(NULL);
	y = 0;
	last = ft_get_last(parse);
	if (*parse != NULL && line[*x] != '-' &&
		ft_is_builtin(line, *x, &y) &&
		ft_caller_sys_fct(parse, paths, line, x)
		&& ft_operator_tool(line, x) == 0)
	{
		if (last->cmd)
			ft_str_tool(last, line, x);
		else
			ft_str_error(last, parse, x , line);
	}
	else
		ft_str_error(last, parse, x , line);
}