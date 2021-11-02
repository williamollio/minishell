

#ifndef MINISHELL_H
# define MINISHELL_H

/* Clear the shell */
#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../libft/libft.h"
#include "stdbool.h" // for boolean variable type
#include <signal.h> // for the signal function
#include <errno.h> // for errno var

/** OP VARIABLE **/
# define PIPE 1 // |
# define OUT 2 // >
# define IN 3 // <
# define LEFT 4 // <<
# define RIGHT 5 // >>

/** FLAG VARIABLE **/
# define BUILT 6
# define SYS 7
# define FILE 8

typedef struct	s_env_list
{
	char				*full;
	char				*var;
	char				*content;
	struct s_env_list	*next;
}			t_env_list;

typedef struct	s_parse
{
	char				*cmd;
	char				*arg;
	char				*str;
	int					op;
	int					flag;
	struct s_parse		*prev;
	struct s_parse		*next;
}			t_parse;

typedef struct s_exec
{
	int		pipes[2];
	pid_t	pid;
	int		temp_fd;
	int		stout;
	int		outfile;
	int		infile;
}			t_exec;

typedef struct s_sys
{
	char	**paths;
	char 	**split;
	char	*pathname;
	char	*cmdpath;
	char 	*join_space;
	char 	*join_arg;
	int		rowsinpath;
	int		x;
}			t_sys;

/** INIT **/
void	ft_silience(char **envp); // hide ^C when hiting control+C
void	ft_init(int argc, char **argv, char **envp, t_env_list **env_head); // initialize the shell

/** BUILDINS FUNCTION **/
void	ft_echo(char  *line);
void	ft_cd(t_env_list **env_head, char  *line);
void	ft_pwd(void);
void	ft_exit(void);
void	ft_unset_node(t_env_list **env_head, char *str);
void	ft_export_node(t_env_list **env_head, char *str);
void	ft_delete_node(t_env_list **env_head, char *str);

/** SYSTEM FUNCTION **/
void	ft_execution(t_parse *test, char **envp, t_env_list **env_head);
void	ft_child_for_sys(t_parse *test, char **envp);
void	ft_child_for_built(t_parse *test, t_env_list **env_head);
void	ft_parent(t_exec *exec);
void	ft_in_is_tempfd(t_exec *exec);
int		ft_redirect_in(t_exec *exec, t_parse **test);
void	ft_redirect_out(t_exec *exec, t_parse *test);
void	ft_pipe(t_exec *exec);
void	ft_fork(t_exec *exec);

/** ERROR MANAGEMENT **/
void	ft_error(char *line);
int		ft_pipe_error(int i, t_parse **parse, char **arr, int op); // check if there is an error when encountering a pipe
int		ft_first(char **paths, int i, t_parse **parse, char **arr); // check if there is an error when reading the first
void	ft_msg_cmd(char *arr); // display message error when command not found
void	ft_msg_pars(char *arr); // display message error when encountering a parse error

/** PARSE **/
int		ft_parsing(char **envp, char *line, t_parse **parse); // general function
int		check_commandpath(char **paths, char *cmd); // check if it's a system function
char	**ft_line_path(char **envp); // line where PATH is in env
int		ft_is_builtin(char *s); // check if the command is built-in
int		ft_operator(int i, t_parse **parse, char **arr); //handle cases where operator appears
int		ft_operator_tool(int i, char **arr); //search for any operator in a string, and return the int corresponding
void	ft_file(int i, t_parse **parse, char **arr, int op); // Initialize str file if needed
void	ft_arg(int *x, t_parse **parse, char **arr); // search for arguments
void	ft_cmd(int *x, t_parse **parse, char **arr); // look at the following variables when encountering a cmd
void	ft_get_env_list(char **envp, t_env_list **env_head);
char	*ft_get_content(char *full);
char	*ft_get_var(char *full);

/** HELPER **/
void	ft_print_list(t_env_list *head);
void	ft_print_list_parse(t_parse **head); // print the list
void	ft_addback_parse(t_parse **head_ref, char *str, int nbr); // create the list
void	ft_free_list_parse(t_parse **head_a); // free the whole list
void	ft_init_parse(t_parse **head); // for each new node created
t_parse	*ft_get_list(t_parse *parse_list); //get parse list from everywhere
t_parse	*ft_get_last(t_parse **head); // return the last node of the list
void	ft_print_node(t_parse *tmp); // print a node
char	**ft_get_paths(char **paths); // get paths variable

#endif

/** TO DO **/
/* free arr in parsing */