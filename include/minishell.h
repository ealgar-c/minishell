/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 11:01:29 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/30 13:30:43 by ealgar-c         ###   ########.fr       */
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


//ast
typedef struct s_ast_node
{
	int					type;
	char				*content;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
}					t_ast_node;

typedef struct s_ast
{
	char		*content;
	t_ast_node	*root;
}					t_ast;

// ast_nodes.c
t_ast_node	*ast_create_node(char *content, int type);
void		ast_add_left(t_ast_node *root, t_ast_node *left);
void		ast_add_right(t_ast_node *root, t_ast_node *right);
t_ast		*ast_init(char *str);

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

// main.c
int			ft_array_len(char **str);
#endif