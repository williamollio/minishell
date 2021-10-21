/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:25:46 by wollio            #+#    #+#             */
/*   Updated: 2021/10/18 12:26:30 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
	char *line;
	clear();
	while (1)
	{
		line = readline(ft_strjoin(getenv("USER"), "\x1b[35m @minishell \x1b[0m>> "));
		if (line != NULL)
			add_history(line);

	}
	return (0);
}

// TESTTETTETETETET