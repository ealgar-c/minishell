/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structs.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 21:20:43 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 13:36:21 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTS_H
# define MINISHELL_STRUCTS_H

# include "minishell.h"
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
	bool				error;
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
	int				pipe_redir_in;
	bool			heredoc_flag;
	char			*heredoc;
	int				redir_out;
	int				pipe_redir_out;
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

// signals
typedef struct s_signals
{
	bool	builtin;
	bool	heredoc;
}	t_signals;

#endif