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
	if (x != 0 && (str1[x - 1] != ' ' && ft_op(str1, x - 1) != 0))
		return (EXIT_FAILURE);
	while ((str1[*i] || str2[*i]) && *i < length)
	{
		if (str1[*i] != str2[*i])
			return (EXIT_FAILURE);
		*i +=1;
	}
	if (str1[*i] == ' ' || ft_op(str1, *i) != 0 || str1[*i] == '\0')
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
	if (ft_strncmp2(&line[x], "echo", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "pwd", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "cd", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "export", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "unset", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "env", x, y) == 0)
		return (EXIT_SUCCESS);
	else if (ft_strncmp2(&line[x], "exit", x, y) == 0)
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

static int	countrows(char **paths)
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

	if (*x != 0 && (line[*x - 1] != ' ' && ft_op(line, *x - 1) == 0))
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
	int		rows;
	char	*cmd;
	int		y;

	(void)parse;
	y = 0;
	//printf("*x %d\n", *x);
	//printf("line[*x] %c\n", line[*x]);
	rows = countrows(paths);
	cmd = ft_clean_sys_fct(line, x, &y);
	i = 0;
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		if (access(ret, F_OK) != -1)
		{
			ft_free1(slash);
			ft_free1(ret);
			*x += y;
			return (EXIT_SUCCESS);
		}
		i++;
	}
	ft_free1(slash);
	ft_free1(ret);
	return (EXIT_FAILURE);
}
