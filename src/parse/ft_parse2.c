#include "../../includes/minishell.h"

// void ft_file(int i, t_parse **parse, char **arr, int op)
// {
// 	if (op >= 2 && op <= 5)
// 	{
// 		ft_addback_parse(parse, arr[i + 1], FILE);
// 		ft_get_last(parse)->op = op;
// 	}
// }

// int ft_operator(int i, t_parse **parse, char **arr)
// {
// 	int	op;

// 	if (arr[i] == NULL || arr[i + 1] == NULL)
// 		return(EXIT_SUCCESS);
// 	op = ft_operator_tool(i, arr);
// 	if ((* parse) != NULL && op != 0)
// 		ft_get_last(parse)->op = op;
// 	if (ft_pipe_error(i, parse, arr, op))
// 		return (EXIT_FAILURE);
// 	ft_file(i, parse, arr, op);
// 	return (EXIT_SUCCESS);
// }

/* NEW */

int	ft_strncmp2(const char *str1, const char *str2, int x, int *i)
{
	int	length;

	length = ft_strlen(str2);

	if (x != 0 && (str1[x - 1] != ' ' && ft_op(str1, x - 1) == 0))
		return (EXIT_FAILURE);
	while ((str1[x + *i] || str2[x + *i]) && *i < length)
	{
		if (str1[x + *i] != str2[*i])
			return (EXIT_FAILURE);
		*i +=1;
	}
	if (str1[x + *i] == ' ' || ft_op(str1, x + *i) != 0 || str1[x + *i] == '\0')
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

void ft_space(char *line, int *x)
{
	while (line[*x] == ' ')
		*x+=1;
}

int	ft_is_builtin(char *line, int x, int *y)
{
	if (ft_strncmp2(line, "echo", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "pwd", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "cd", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "export", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "unset", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "env", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(line, "exit", x, y) == 0)
		return (EXIT_SUCCESS);
	else
		return (EXIT_FAILURE);
}

int ft_caller_builtin(t_parse **parse, char *line, int *x)
{
	int		y;
	char	*str;

	y = 0;
	if (!ft_is_builtin(line, *x, &y))
	{
		str = ft_substr(line, *x, y);
		ft_addback_parse(parse, str, BUILT);
		*x += y;
		return (EXIT_SUCCESS);
	}
	return (EXIT_FAILURE);
}

int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

int ft_op(const char *line, int i)
{
	if (line[i] == '|')
		return (1);
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (4);
		return (3);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (5);
		return (2);
	}
	else
		return (EXIT_SUCCESS);
}

char *ft_clean_sys_fct(char *line, int *x, int *y)
{
	char	*cmd;

	if ((line[*x] == ' ' || ft_op(line, *x) != 0) ||
		(*x != 0 && (line[*x - 1] != ' ' && ft_op(line, *x - 1) == 0)))
		return (NULL);
	while (line[(*x) + (*y)] && ft_op(line, (*x) + (*y)) == 0
			&& line[(*x) + (*y)] != ' ')
			*y +=1;
	if (line[(*x) + (*y)] == ' ' || ft_op(line, (*x) + (*y)) != 0 || line[(*x) + (*y)] == '\0')
	{
		cmd = ft_substr(line, *x, *y);
		return (cmd);
	}
	else
		return (NULL);
}

int ft_caller_sys_fct(t_parse **parse, char **paths, char *line, int *x)
{
	int		i;
	char	*ret;
	char	*slash;
	char	*cmd;
	int		y;
	int		rows;

	y = 0;
	cmd = ft_clean_sys_fct(line, x, &y);
	i = 0;
	rows = countrows(paths);
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		ft_free1(slash);
		if (access(ret, F_OK) != -1)
		{
			*x += y;
			ft_free1(ret);
			ft_addback_parse(parse, cmd, SYS);
			return (EXIT_SUCCESS);
		}
		ft_free1(ret);
		i++;
	}
	return (EXIT_FAILURE);
}
