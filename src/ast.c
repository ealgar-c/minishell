/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 14:17:03 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/19 15:48:22 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	print_ast(t_ast_node *node)
{
	int	i;

	if (!node)
		return ;
	i = 0;
	print_ast(node->left);
	while (i < node->type)
	{
		ft_printf(" ");
		i++;
	}
	ft_printf("%s\n", node->content);
	print_ast(node->right);
}

void	tree(t_ast_node *node, char **cmd, int curr)
{
	int	a;

	if (!node)
		return ;
	a = curr;
	if (ft_strchr(cmd[a], '|') != NULL)
	{
		ast_add_left(node, ast_create_node(cmd[a], 0));
		tree(node->left, cmd, curr + 1);
	}
	else
	{
		ast_add_right(node, ast_create_node(cmd[a], curr));
		tree(node->right, cmd, curr + 1);
	}
}

t_ast	*create_tree(char *fullcmd)
{
	char	**cmd;
	t_ast	*ast;

	ast = ast_init(fullcmd);
	cmd = ft_split(fullcmd, ' ');
	// ahora cmd es un array de strings separado por las pipes
	ast_add_root(ast, ast_create_node("|", 0));
	tree(ast->root, cmd, 0);
	print_ast(ast->root);
	return (ast);
}
/* t_ast	*create_tree(char *fullcmd)
{
	char	**cmd;
	t_ast	*ast;

	ast = ast_init(fullcmd);
	cmd = ft_split(fullcmd, '|');
	// ahora cmd es un array de strings separado por las pipes
	ast_add_root(ast, ast_create_node("|", 0));
	// ahora el nodo raiz del arbol es una pipe
	ast_add_left(ast->root, ast_create_node(cmd[0], 1));
	// ahora el hijo izquierdo del nodo raiz es el primer comando
	ast_add_right(ast->root, ast_create_node(cmd[1], 1));
	// ahora el hijo derecho del nodo raiz es el segundo comando
	ast_add_left(ast->root->left, ast_create_node("echo", 2));
	// ahora el hijo izquierdo del hijo izquierdo del nodo raiz es el comando echo
	ast_add_right(ast->root->left, ast_create_node("hola", 2));
	ast_add_left(ast->root->left->right, ast_create_node("sigamos", 3));
	ast_add_right(ast->root->left->right, ast_create_node("abriendo", 3));
	print_ast(ast->root);
	return (ast);
} */
