/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akurz <akurz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 19:22:31 by wollio            #+#    #+#             */
/*   Updated: 2021/10/25 14:45:38 by akurz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* Clear the shell */
#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"

typedef struct	s_env_list
{
	char				*full;
	char				*var;
	char				*content;
	struct s_env_list	*next;
}			t_env_list;

int main();

/** BUILDINS FUNCTION **/
void	ft_echo(char  *line);
void	ft_cd(char  *line);
void	ft_pwd(char  *line);
void	ft_export(char  *line);
void	ft_unset(char  *line);
void	ft_env(char **envp);
void	ft_exit(void);

/** SYSTEM FUNCTION **/
void	ft_sys_funct_ex(char *line);
void	ft_sys_funct_chck(char *line);

/** ERROR MANAGEMENT **/
void	ft_error(char *str);

//** PARSE **/
// void	ft_parse_input(char **envp, char *line);
void	ft_get_env_list(char **envp, t_env_list **env_head);
void	ft_export_node(t_env_list **env_head, char *str);
void	ft_delete_node(t_env_list **env_head, char *str);
void	ft_print_list(t_env_list *head);


#endif
