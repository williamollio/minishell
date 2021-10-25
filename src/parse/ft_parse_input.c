/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 15:24:01 by akurz             #+#    #+#             */
/*   Updated: 2021/10/22 21:46:18 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	countrows(char **paths)
{
	int	i;

	i = 0;
	while (paths[i] != NULL)
		i++;
	return (i);
}

int	check_commandpath(int rows, char **paths, char *cmd)
{
	int		i;
	char	*ret;
	char	*slash;

	i = 0;
	while (i <= rows)
	{
		slash = ft_strjoin(paths[i], "/");
		ret = ft_strjoin(slash, cmd);
		if (access(ret, F_OK) != -1)
			return (1);
		i++;
	}
	return (0);
}

int	is_builtin(char *s)
{
	if (ft_strncmp(s, "echo", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "pwd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "cd", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "export", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "unset", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "env", ft_strlen(s)) == 0)
		return (1);
	else if (ft_strncmp(s, "exit", ft_strlen(s)) == 0)
		return (1);
	else
		return (0);
}

void	ft_parse_input(char **envp, char *line)
{
	char	**args;
	char	*pathname = NULL;
	char	**paths = NULL;
	int		i;
	int		x;
	int		s;
	int		b;
	int		rowsinpath;
	t_parse	parse;


	parse.system = malloc(sizeof(char **));
	parse.builtin = malloc(sizeof(char **));
	args = ft_split(line, ' ');
	x = 0;
	rowsinpath = 0;
	while (envp[x] != NULL)
	{
		if (envp[x][0] == 'P' && envp[x][1] == 'A'
		&& envp[x][2] == 'T' && envp[x][3] == 'H')
		{
			pathname = ft_substr(envp[x], 5, ft_strlen(envp[x]) - 5);
			paths = ft_split(pathname, ':');
			rowsinpath = countrows(paths);
			break ;
		}
		x++;
	}
	s = 0;
	b = 0;
	i = 0;
	while (args[i])
	{
		if (is_builtin(args[i]) == 1)
		{
			printf("args = %s\n", args[i]);
			// parse.builtin[b] = malloc(sizeof(char *));
			parse.builtin[b] = args[i];
			b++;
		}
		else if (check_commandpath(rowsinpath, paths, args[i]) == 1)
		{
			printf("args = %s\n", args[i]);
			// parse.system[s] = malloc(sizeof(char *));
			parse.system[s] = args[i];
			s++;
		}
		i++;
	}
	printf("builtin[0] = %s\n", parse.builtin[0]);
	printf("builtin[1] = %s\n", parse.builtin[1]);
	printf("system[0] = %s\n", parse.system[0]);
	printf("system[1] = %s\n", parse.system[1]);
	exit(0);
}
