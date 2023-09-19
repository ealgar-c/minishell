/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_nodes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:22:45 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/08/30 14:21:34 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_ast_node	*ast_create_node(char *content, int type)
{
	t_ast_node	*node;

	node = malloc(sizeof(t_ast_node));
	if (!node)
		return (NULL);
	node->content = content;
	node->type = type;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

void	ast_add_left(t_ast_node *root, t_ast_node *left)
{
	root->left = left;
}

void	ast_add_right(t_ast_node *root, t_ast_node *right)
{
	root->right = right;
}

t_ast	*ast_init(char *str)
{
	t_ast	*ast;

	ast = malloc(sizeof(t_ast));
	if (!ast)
		return (NULL);
	ast->content = str;
	ast->root = NULL;
	return (ast);
}

void	ast_add_root(t_ast *ast, t_ast_node *root)
{
	ast->root = root;
}
