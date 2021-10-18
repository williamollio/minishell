/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wollio <wollio@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:25:46 by wollio            #+#    #+#             */
/*   Updated: 2021/10/15 14:32:35 by wollio           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main()
{
    while(1)
    {
        char *str;
        char *line;
        str = getenv("USER");
        printf("%s\n", str);
        line = readline(str);
        //printf("%s\n", line);
        //sleep(1);
    }
    return (0);
}
