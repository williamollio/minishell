#include "../../includes/minishell.h"

char **ft_line_path(char **envp)
{
	int		x;
	char	*pathname;
	char	**paths;

	paths = NULL;
	x = 0;
	while (envp[x] != NULL)
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'A'
		&& envp[x][2] == 'T' && envp[x][3] == 'H')
		{
			pathname = ft_substr(envp[x], 5, ft_strlen(envp[x]) - 5);
			paths = ft_split(pathname, ':');
			break ;
		}
		x++;
	}
	ft_get_paths(paths);
	return (paths);
}

// char	*ft_get_next_word(char *line, int *i)
// {
// 	char	*ret;
// 	int		x;

// 	(*i)++;
// 	while (line[*i] == ' ')
// 		(*i)++;
// 	x = (*i);
// 	while (ft_operator_tool2(line, i) == 0 && line[x] != ' ' && line[x] != '\0')
// 		x++;
// 	ret = ft_substr(line, (*i), x - (*i));
// 	return (ret);
// }

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
			if (split[1] != NULL)
			{
				cmd = ft_create_cmd(split, count);
				ft_add_next(parse, temp, cmd, CMD);
			}
			ft_free2(split);
		}
		temp = temp->next;
	}
}

void	ft_splitter(t_parse **parse)
{
	t_parse	*temp;
	int		count;

	temp = *parse;
	while (temp != NULL)
	{
		if (temp->str != NULL && !temp->cmd)
		{
			temp->cmd = ft_split2(temp->str, ' ', &count);
			// free(temp->str); // look into this (double free)
			temp->str = "";
		}
		temp = temp->next;
	}
}

int ft_parsing(char **envp, char *line, t_parse **parse)
{
	*parse = NULL;

	(void)envp;
	if (ft_lexer(line, parse) < 0)
	{
		ft_putendl_fd("unclosed quotes", 2);
		// return error here
	}
	ft_seperator(parse);

	ft_splitter(parse);

	return (EXIT_SUCCESS);
}
