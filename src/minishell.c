/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:01 by wollio            #+#    #+#             */
/*   Updated: 2021/11/23 18:19:32 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit_status;

int	main(int argc, char **argv, char **envp)
{
	t_env		*env_head;
	t_parse		*parse;
	t_main		main;

	main.fd_in_old = dup(0);
	main.fd_out_old = dup(1);
	ft_init(argc, argv, envp, &env_head);
	while (1)
	{
		dup2(main.fd_in_old, 0);
		dup2(main.fd_out_old, 1);
		signal(SIGINT, &ft_sigint);
		signal(SIGQUIT, SIG_IGN);
		main.line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m"));
		if (main.line == NULL)
			exit(EXIT_SUCCESS);
		main.s1 = ft_strtrim(main.line, " ");
		if (main.s1 && !ft_parsing(main.line, &parse, &env_head))
			ft_execution(parse, envp, &env_head);
		add_history(main.line);
		if (main.s1)
			ft_free1(main.s1);
		ft_free_list_parse(&parse);
	}
	return (0);
}
