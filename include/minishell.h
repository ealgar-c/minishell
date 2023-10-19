/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/19 16:10:15 by ealgar-c         ###   ########.fr       */
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

// ENUM
typedef enum e_tokens
{
	CMD = 0,
	ARG,
	PIPE,
	GREAT, // > REDIR_OUT
	GREAT_GREAT, // >> APPEND
	LESS, // < REDIR_IN
	LESS_LESS, // << HEREDOC
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
	int				redir_out;
	bool			double_out;
	bool			pipe;
	struct s_parser	*prev;
	struct s_parser	*next;
}		t_parser;
// utils
struct	s_lexer;

typedef struct s_ast_utils
{
	int					pipes;
	struct s_lexer		*lexer_root;
	struct s_parser		*parser_root;
	struct s_env		*env_root; //esto aún no está inicializado
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

// FUNCIONES

// parser.c
void			ft_parser(t_info *info);

// parser_arguments_utils.c
t_parser_args	*par_newargnode(char *content);
void			get_arguments(t_lexer *lex, t_parser *par);
void			get_final_cmd(t_parser *node);

// lexer.c
void			ft_lexer(char *str, t_info *info);

// lexer_utils.c
t_ast_utils		*ft_utils_init(void);
t_lexer			*new_lexer_node(char *content, int token, t_ast_utils *utils);
void			ft_lxadd_back(t_lexer **root, t_lexer *new);
bool			ft_check_last_node(t_ast_utils *utils);

// builtins.c
void			ft_exit(char **cmd, t_info *info);

//void		ft_unset(char **cmd);
void			ft_unset(t_parser *parser_node, t_info *info);

//builtin_env.c
void			ft_env(t_parser *parser_node, t_info *info);

// builtin_cd.c
void			ft_cd(t_parser *parser_node, t_info *info);

// builtin_pwd.c
void			ft_pwd(t_parser *parser_node, t_info *info);

// builtin_echo.c
void			ft_echo(t_parser *parser_node, t_info *info);

// builtin_export.c
void			ft_export(t_parser *parser_node, t_info *info);

// builtin_unset.c
void			ft_unset(t_parser *parser_node, t_info *info);

// executer.c
void			ft_executer(t_info *info);
void			ft_redirector(t_parser *parser_node);

// main.c
int				ft_array_len(char **str);

// free_utils.c
void			ft_free_utils(t_info *info, bool mode);
void			ft_free(char **str);

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

#endif