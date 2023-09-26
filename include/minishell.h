/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/26 15:58:41 by ealgar-c         ###   ########.fr       */
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

/* //ast
typedef struct s_ast_utils
{
	int	num_pipes;
	int	num_cmds;
}	t_ast_utils;

typedef struct s_ast_node
{
	int					type; // token para saber si es un pipe, un comando, etc HACER ENUM
	int					index; // el indice del nodo en el arbol
	char				*content; // el contenido del nodo
	struct s_ast_node	*next;
	struct s_ast_node	*prev;
	struct s_ast_utils	*utils;
}					t_ast_node;

typedef struct s_ast
{
	char		*content;
	t_ast_node	*root;
}					t_ast;

// functions

// ast_nodes.c
t_ast_node	*ast_create_node(char *content, int type);
void		ast_add_left(t_ast_node *root, t_ast_node *left);
void		ast_add_right(t_ast_node *root, t_ast_node *right);
t_ast		*ast_init(char *str);
void		ast_add_root(t_ast *ast, t_ast_node *root);

// ast.c
t_ast		*create_tree(char *fullcmd);
 */

typedef enum e_tokens
{
	CMD = 0,
	ARG,
	PIPE,
	GREAT, // >
	GREAT_GREAT, // >> APPEND
	LESS, // <
	LESS_LESS, // << HEREDOC
}	t_tokens;

// parser

typedef struct s_parser_utils
{
	struct s_parser	*root;
	bool			syntax_checker;
	int				pipes;
	
}	t_parser_utils;

typedef struct s_parsermio
{
	int				i;
	char			*cmd;
	t_tokens		token;
	struct s_parser	*next;
}	t_parsermio;

typedef struct s_parser
{
	char			*cmd;
	char			*arg;
	void			*function; // no sé cómo se hace pero pa acordarme
	char			*redir_in;
	bool			heredoc_flag;
	char			*redir_out;
	bool			double_out;
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

// funcs

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
void		execute_process(char **cmd, char **envp);
void		executer(char **cmd, char **envp);
void		get_cmds(char *str, bool final, char **envp);

// main.c
int			ft_array_len(char **str);
#endif