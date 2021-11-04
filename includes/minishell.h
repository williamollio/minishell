

#ifndef MINISHELL_H
# define MINISHELL_H

/* Clear the shell */
#define clear() printf("\033[H\033[J")

#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/param.h>
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
	int		cmdcount;
}			t_exec;

typedef struct s_sys
{
	char	**paths;
	char 	**split;
	char	*pathname;
	char	*cmdpath;
	char 	*join_space;
	char 	*join_arg;
	char 	*join_str;
	int		rowsinpath;
	int		x;
}			t_sys;

/** INIT **/
void	ft_silience(char **envp); // hide ^C when hiting control+C
void	ft_init(int argc, char **argv, char **envp, t_env_list **env_head); // initialize the shell
void	ft_sigint(int signal); // handle ctrl + c
void	ft_tool(int *fd_in_old, int *fd_out_old); // contain signal handling and fd dup

/** BUILDINS FUNCTION **/
void	ft_echo(char  *str, char *arg);
void	ft_cd(t_env_list **env_head, char  *line);
void	ft_pwd(void);
void	ft_exit(void);
void	ft_unset_node(t_env_list **env_head, char *str);
void	ft_export_node(t_env_list **env_head, char *str);
void	ft_delete_node(t_env_list **env_head, char *str);

/** EXECUTION **/
void	ft_execution(t_parse *test, char **envp, t_env_list **env_head); // main of pipex part
void	ft_child_for_sys(t_parse *test, char **envp); // execute system commands
void	ft_child_for_built(t_parse *test, t_env_list **env_head); // execute builtin commands
void	ft_parent(t_exec *exec); // output of last commands pipe will now ne in temp_fd
void	ft_in_is_tempfd(t_exec *exec); // childs always read from temp_fd --> redirect temp_fd to be input
int		ft_redirect_in(t_exec *exec, t_parse **test); // takes input either from infile or stdin
void	ft_redirect_out(t_exec *exec, t_parse *test); // redirect output either to file, stdout or pipe
void	ft_pipe(t_exec *exec); // creates a pipe for interprocess communication
void	ft_fork(t_exec *exec); // fork a process

/** ERROR MANAGEMENT **/
void	ft_error(char *line);
int		ft_pipe_error(int i, t_parse **parse, char **arr, int op); // check if there is an error when encountering a pipe
int		ft_first(char **paths, int i, t_parse **parse, char **arr); // check if there is an error when reading the first
void	ft_msg_cmd(char *arr); // display message error when command not found
void	ft_msg_pars(char *arr); // display message error when encountering a parse error
void	ft_msg_arg(char *arr); // display message error when encountering an option with a built-in

/** PARSE **/
int		ft_parsing(char **envp, char *line, t_parse **parse); // general function
int		check_commandpath(char **paths, char *cmd); // check if it's a system function
char	**ft_line_path(char **envp); // line where PATH is in env
//int		ft_is_builtin(char *s); // check if the command is built-in
int		ft_operator(int i, t_parse **parse, char **arr); //handle cases where operator appears
int		ft_operator_tool(int i, char **arr); //search for any operator in a string, and return the int corresponding
void	ft_file(int i, t_parse **parse, char **arr, int op); // Initialize str file if needed
int		ft_arg(int *x, t_parse **parse, char **arr); // search for arguments
void	ft_get_env_list(char **envp, t_env_list **env_head); // turns env variable into a list
char	*ft_get_content(char *full); // returns content from env string
char	*ft_get_var(char *full); // returns var from env string

/* NEW PARSING */
void	ft_space(char *line, int *x); // skip spaces
int		ft_caller_builtin(t_parse **parse, char *line, int *x); // call the function ft_is_buildin and creates a node if necessary
int		ft_is_builtin(char *line, int x, int *y); // check if the command is built-in
int		ft_strncmp2(const char *str1, const char *str2, int num, int *i); // takes a pointer as in index

int		ft_op(const char *line, int i); // look for operators
int		ft_caller_sys_fct(t_parse **parse, char **paths, char *line, int *x); // call the function checkcommand
char		*ft_clean_sys_fct(char *line, int *x, int *y); // cleaner for builtin

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
char	*ft_extract_content(t_env_list *env_head, char *var); // returns the value of the env variable you pass in to it

#endif

/** TO DO **/
/* free arr in parsing */
/* implement ft_tool in minishel.c */


/** -------------------------------- alex -------------------------------- **/
/* when minishell starts, OLDPWD shouldnt exist */
/* add heredoc (<<) */
/* init struct vars */
/* execute builtins in child when theres morethen 1 cmd */
