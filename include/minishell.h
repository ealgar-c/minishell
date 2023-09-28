/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/28 12:44:47 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>

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

// parser

typedef struct s_parser
{
	char			*cmd;
	int				redir_in;
	bool			heredoc_flag;
	int				redir_out;
	bool			double_out;
	bool			pipe;
	struct s_parser	*prev;
	struct s_parser	*next;
}		t_parser;

// lexer

struct	s_lexer;

typedef struct s_ast_utils
{
	int				pipes;
	int				lexer_len;
	struct s_lexer	*lexer_root;
	struct s_parser	*parser_root;
	struct s_env	*env_root; //esto aún no está inicializado
}	t_ast_utils;

typedef struct s_lexer
{
	struct s_ast_utils	*utils;
	int					i;
	t_tokens			token;
	char				*content;
	struct s_lexer		*prev;
	struct s_lexer		*next;
}	t_lexer;

typedef struct	s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;

}	t_env;

// funcs

// parser.c
t_parser	*ft_parser(t_ast_utils *utils);
// lexer.c
t_lexer		*new_lexer_node(char **content, int token, int i, t_ast_utils *utils);
void		ft_lxadd_back(t_lexer **root, t_lexer *new);
int			ft_token_type(char **str, t_ast_utils *utils, int i);
t_ast_utils	*ft_utils_init(void);
t_lexer		*ft_lexer(char **cmdsplit);

// builtins.c
void		ft_pwd(char **cmd);
void		ft_exit(char **cmd);
void		ft_echo(char **cmd);
void		ft_cd(char **cmd);
void		ft_export(char **cmd);
void		ft_unset(char **cmd);
void		ft_env(char **cmd);

// filter.c
void		ft_filter(char **cmd, char **envp);

// executer.c
void	execute_process(t_parser *parser_node, char **envp);
void	executer(t_ast_utils *utils, char **envp);
void		get_cmds(char *str, bool final, char **envp);

// main.c
int			ft_array_len(char **str);
#endif