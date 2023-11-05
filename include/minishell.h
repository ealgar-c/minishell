/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/05 19:35:37 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

t_signal	g_signals;
// ENUM
typedef enum e_tokens
{
	CMD = 0,
	ARG,
	PIPE,
	GREAT,
	GREAT_GREAT,
	LESS,
	LESS_LESS,
	REDIR_FILE,
}	t_tokens;

typedef enum e_quoted
{
	NONE = 0,
	SINGLE,
	DOUBLE,
}	t_quoted;

// STRUCTS
// info
typedef struct s_info
{
	struct s_env		*env_root;
	struct s_ast_utils	*utils;
	int					exit_status;
	int					stdin_cpy;
	int					stdout_cpy;
}	t_info;

// parser
typedef struct s_parser_args
{
	char					*str;
	struct s_parser_args	*next;
}	t_parser_args;

typedef struct s_parser
{
	t_parser_args	*tmp_arg;
	char			**cmd;
	int				redir_in;
	bool			heredoc_flag;
	char			*heredoc;
	int				redir_out;
	bool			double_out;
	bool			pipe;
	struct s_parser	*prev;
	struct s_parser	*next;
}		t_parser;
struct		s_lexer;
// utils

typedef struct s_ast_utils
{
	int					pipes;
	struct s_lexer		*lexer_root;
	struct s_parser		*parser_root;
	struct s_env		*env_root;
	struct s_info		*info;
}	t_ast_utils;

// lexer
typedef struct s_lexer
{
	struct s_ast_utils	*utils;
	int					i;
	t_tokens			token;
	char				*content;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;

// env
typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
	struct s_env	*prev;

}	t_env;

typedef struct s_signals
{
	bool	builtin;
	bool	heredoc;
	bool	error;
}	t_signals;


/************************FUNCIONES***************************/

void			ctrlc_handler(int sign);
/*							LEXER							*/
// lexer.c
void			ft_lexer(char *str, t_info *info);

// lexer_utils.c
bool			ft_token_check(char c);
char			*ft_add_space(char *str, int s, char *content, char q);
//char			*ft_quote_handling(char *str, int i, char q, int tk);
char			*get_content(char *str, int i, int token, t_info *info);

// lexer_list_utils.c
t_ast_utils		*ft_utils_init(t_info *info);
t_lexer			*new_lexer_node(char *content, int token, t_ast_utils *utils);
void			ft_lxadd_back(t_lexer **root, t_lexer *new);
bool			ft_check_last_node(t_ast_utils *utils);

/*							PARSER							*/
// parser.c
void			ft_parser(t_info *info);

// parser_arguments_utils.c
t_parser_args	*par_newargnode(t_lexer *tmp);
void			get_arguments(t_lexer *lex, t_parser *par);
void			get_final_cmd(t_parser *node);

/*							EXECUTER						*/
// redirections.c

void			ft_redirector(t_parser *parser_node, t_info *info);
void			ft_redirector_builtinpipes(t_parser *parser_node, t_info *info);
void			ft_redirector_back(t_info *info);
int				ft_heredoc(t_parser *parser, t_info	*info);

// builtins.c
void			ft_exit(char **cmd, t_info *info);

//void		ft_unset(char **cmd);
void			ft_unset(t_parser *parser_node, t_info *info);

//builtin_env.c
void			ft_env(t_parser *parser_node, t_info *info);

// builtin_cd.c
void			ft_cd(t_parser *parser_node, t_info *info);

// builtin_pwd.c
void			ft_pwd(t_info *info);

// builtin_echo.c
void			ft_echo(t_parser *parser_node, t_info *info);

// builtin_export.c
void			ft_export(t_parser *parser_node, t_info *info);
// builtin_export_utils.c
void			ft_non_arg_export(t_info *info);

// builtin_unset.c
void			ft_unset(t_parser *parser_node, t_info *info);

// executer.c
void			ft_executer(t_info *info);
void			ft_builtin(t_parser *parser_node, char **cmd, t_info *info);
char			**env_to_array(t_info *info);
char			*get_useful_path(char *cmd, t_env *env_root);
// executer_utils.c
void			ft_non_builtin(t_info *info, t_parser *parser, char *path);


// extensor.c
char			*check_extensor(char *content, t_info *info, int quoted);

// enviroment.c
t_env			*save_envp(char **envp);
t_env			*ft_new_env_node(char *name, char *value);
void			env_add_back(t_env **root, t_env *new);
char			*ft_get_env_name(char *fullenv);
char			*ft_get_env_value(char *fullenv);

// extend_and_quote.c
void			ft_extend_and_quotes(char **cmd, t_info *info);
char			*clean_quotes(char *str);

// pipes_config.c
void			config_pipes(t_parser *parser, int mode, t_info *info);

/*							UTILS							*/
//errors.c
void			ft_error_handling(int error, char *str, t_info	*info);
// free_utils.c
void			ft_free_utils(t_info *info, bool mode);
void			ft_free_env(t_env *root);
void			ft_free(char **str);

#endif