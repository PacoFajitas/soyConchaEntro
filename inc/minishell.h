/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfiguero <tfiguero@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 15:36:05 by mlopez-i          #+#    #+#             */
/*   Updated: 2024/03/22 19:29:41 by tfiguero         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/*	LIBRARIES	*/
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
# include <sys/errno.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
# include "./libft/libft.h"

/*	DEFINES		*/
# define SPACES		0 // 0 = ESPACIOS
# define STRING		1 // 1 = STRING SIN COMILLAS
# define STRINGCS	2 // 2 = STRING CON COMILLAS SIMPLES
# define STRINGCD	3 // 3 = STRING CON COMILLAS DOBLES
# define PIPE 		4 //  = PIPE |
# define HDOC		5 //  = HEREDOC <<
# define REDIROUT	6 //  = REDIRECCION >
# define APPEND		7 //  = APEND >>
# define REDIRIN	8 //  = REDIRECCION <
//# define DOLLAR		9 //  = $

/*	STRUCTS		*/
/*	struct with tokens	*/
typedef struct s_token
{
	char			*content;
	int				type;
	int				expanded;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;
/*	environment struct	*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;
/*	filedescriptors struct	*/
typedef struct s_fd
{
	int			fd;
	int			type;
	char		*str;
	struct s_fd	*next;
}	t_fd;
/*	struct of pipes and info	*/
typedef struct s_pipe
{
	char			**cmds;
	char			*path;
	int				in;
	int				out;
	int				builtin;
	struct s_fd		*fds;
	struct s_pipe	*next;
}	t_pipe;

/*	struct containing all general data	*/
typedef struct s_data
{
	char	*line;
	int		pipes;
	int		exp;
	t_token	*token;
	t_env	*env;
	t_env	*export;
	t_fd	*fds;
	t_pipe	*p;
	int		fd[2];
	pid_t	pid;
	int		error;
	int		status;
	int		exit;
	int		off;
}	t_data;

int	g_sig;

/*	FUNCTIONS	*/
/*	BUILTINS	*/
/*	cd.c	*/
int			ft_cd_access(t_data *data, char *path);
char		*ft_getcwd(void);
int			ft_cd_path(t_env **env, t_env **exp, char *path, char *oldpwd);
int			ft_cd(t_data *data, t_pipe *p, t_env **env, t_env **exp);
/*	echo.c	*/
int			ft_echo(t_pipe *pipe, int n_flag, int i);
/*	exit.c	*/
int			ft_exit_b(t_pipe *p, t_data *data, int num, int err);
int			ft_exit(t_data *data);
/*	pwd.c	*/
void		ft_pwd(t_pipe *p, t_data *data);
/*	unset.c	*/
void		ft_unset_node(t_env **env, int i);
void		ft_unset_export(t_data **data, t_env *tmp, int i, char *key);
int			ft_unset(t_pipe *p, t_data **data);

/*	ENV	*/
/*	env_utils.c	*/
t_env		*ft_new_node(char *key);
void		ft_add_env(t_env **env, t_env *new);
void		ft_sort_env(t_env **env);
char		**ft_env_to_array(t_env **env);
void		ft_change_env_value(char *key, char *value, t_env **env);
/*	env_utils2.c*/
int			ft_count_env(t_env *env);
/*	env.c	*/
int			ft_get_env(char **envp, t_env **env);
void		ft_init_new_env(t_env **env);
void		ft_shlvl(t_env **env, t_env *temp, int shlvl, char *str);
int			ft_print_env(t_env **env, t_pipe *p);
void		ft_free_env(t_env **env);

/*	ERRORS	*/
/*	errors.c	*/
int			ft_exit_error(char *cmd, char *msg);
int			ft_error_exit(t_data *data, char *name, char *message, int err);
int			ft_error_ret(t_data *data, char *name, char *message, int err);
int			ft_error(char *cmd, char *line, char *name, char *message);

/*	EXECUTOR	*/
/*	exec_utils.c	*/
void		ft_check_open(t_pipe *p, t_fd *fd, int prev);
int			ft_check_open_builtin(t_data *data, t_pipe *p, t_fd *fd);
int			ft_open_builtin(t_data *data, t_pipe *p, t_fd *fd, int prev);
int			ft_check_open_file(t_data *data, t_pipe *p, t_fd *fd);
void		ft_open_file(t_data *data, t_pipe *p, t_fd *fd, int prev);

/*	exec_utils2.c	*/
void		ft_redir(t_pipe *p);
int			ft_check_builtin(t_pipe *p);
int			ft_check_access_file(char *str, int mode);
void		exit_status(t_data	*data, int j);
/*	executor.c	*/
int			ft_execute_builtin(t_data *data, t_pipe *p);
void		ft_check_access(t_data *data, char **cmd, t_pipe *p);
void		ft_child_process(t_data *data, t_pipe *p, int last);
int			ft_last_process(t_data *data, t_pipe *p);
int			ft_executor(t_data *data, t_pipe *p);

/*	EXPANSOR	*/
/*	expan_utils.c	*/
int			ft_check_ex_ifs(char *str, int *i);
char		*ft_ex_ifs(t_data *data, char *str, char *cont, int *i);
char		*ft_expand_string(char *str, t_data *data, int i, int *exp);
char		*ft_exdqu_ifs(char *str, t_data *data, char *cont, int *i);
char		*ft_expand_dquoted(char *str, t_data *data, int i);
/*	expand_utils2.c	*/
int			ft_is_letter(char c);
char		*ft_strjoin_char(char *str, char add);
/*	expansor.c	*/
char		*ft_expand_content(t_data *data, t_token *tmp, int *exp);
t_token		*ft_expan(t_token **token, t_data *data, int type, int *exp);

/*	EXPORT	*/
/*	export_utils.c	*/
t_env		*ft_init_new_export(t_env **env);
char		*ft_get_env_value(t_env **env, char *key);
void		ft_add_export(char *str, t_env **env);
int			ft_check_equal(char	*str);
t_env		*ft_search_keys(char *key, t_env **list);
/*	export.c	*/
void		ft_filter_export2(t_data **data, char *str,
				t_env *temp, t_env *temp2);
void		ft_filter_export(t_data **data, char *str, char *key, t_env *temp2);
int			ft_export(t_data **data, t_pipe *p, int i);
void		ft_print_export(t_data *data, int fd);

/*	LEXER	*/
/*	lexer_merge.c	*/
void		ft_look_for_quotes(t_token **token);
void		ft_assign(t_token **token, t_token *new,
				t_token *temp, t_token *start);
int			ft_dollar_last(char *str);
t_token		*ft_merge_tokens(t_token **token);
/*	lexer_utils.c	*/
t_token		*ft_new_token(char *content, int token, int exp);
void		ft_add_token(t_token **token, t_token *new);
void		ft_free_token(t_token **token);
char		*ft_clean_line(char *line);
/*	lexer.c	*/
t_token		*ft_quote_token(char *line, int *i);
t_token		*ft_str_token(char *line, int *i);
t_token		*ft_meta_token(char *line, int *i, t_data *data);
t_token		*ft_space_token(char *line, int *i);
int			ft_tokenize(t_data *data, char *line, t_token *token, int i);

/*	PARSER	*/
/*	parser_utils.c	*/
void		ft_init_pipe(t_pipe *p);
void		ft_add_pipe(t_pipe **pipe, t_pipe *new);
void		ft_free_pipe(t_pipe **p);
/*	parser.c	*/
int			parse_redirs(t_data *data, t_token **tmp);
int			parse_cmds(t_data *data, t_pipe *p, t_token **tmp);
int			ft_skip_redirs(t_token **tmp, t_pipe *p, t_fd **fd);
int			ft_parser(t_data *data, t_token **token, int ret, t_fd *fd);

/*	SIGNALS	*/
/*	signals.c	*/
int			init_signals(int mode);
void		do_sigign(int signum);
void		norm_handler(int sig, siginfo_t *data, void *non_used_data);
void		heredoc_handler(int sig, siginfo_t *data, void *non_used_data);
void		ninter_handler(int sig, siginfo_t *data, void *non_used_data);

/*	SYNTAX	*/
/*	syntax.c	*/
char		*ft_syntax_char(t_token *token);
int			ft_print_syntax_error(t_data *data, t_token *tmp,
				int error, int exit);
int			ft_syntax_pipe(t_token *tmp, t_data *data);
int			ft_syntax_redirs(t_token **tmp);
int			ft_syntax_error(t_data *data, t_token **token);

/*	UTILS	*/
/*	fd_utils.c	*/
void		init_fd(t_fd *fd, int t, int fdt);
void		ft_add_fd(t_fd **fd, t_fd *new);
int			ft_save_hd(char *key, t_env **env);
char		*ft_expand_hd(char *str, t_env **env, int i);
/*	fd_utils2.c	*/
int			ft_heredoc(t_data *data, char *key);
void		ft_free_fds(t_fd **fd);
/*	lst_utils.c	*/
char		**ft_token_to_array2(char **cmds, int *i);
char		**ft_token_to_array(t_token **token, char **cmds, int i);
char		**ft_aux_array_if(t_token *tmp, char **array, int *i, int j);
char		**ft_aux_array_else(t_token *tmp, char **array, int *i);
char		**ft_aux_array(t_token *tmp, char **array, int i);
/*	lst_utils2.c	*/
int			ft_lstsize(t_token *lst);
char		*ft_get_cmd_path(t_env **env, char *cmd);
int			ft_count_spaces(char *str);
int			ft_check_for_malloc(char *str, int j);
/*	mem_utils.c	*/
void		*ft_memdel(void *ptr);
char		**ft_free_array(char **array);

/*	SRC	*/
/*	init_data.c	*/
int			ft_init_envs(t_env **env, t_env **export, char **envp);
int			ft_init_data(t_data *data, char **envp);
void		ft_clean_data(t_data *data);
void		ft_clean_all_data(t_data *data);

#endif