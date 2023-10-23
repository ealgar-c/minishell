/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 12:20:00 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/23 17:24:41 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_lxadd_back(t_lexer **root, t_lexer *new)
{
	t_lexer	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	ptr->next->prev = ptr;
}

t_lexer	*new_lexer_node(char *content, int token, t_ast_utils *utils)
{
	t_lexer	*new_node;

	if (content == NULL)
		return (NULL);
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->utils = utils;
	if (utils->lexer_root)
		ft_lxadd_back(&utils->lexer_root, new_node);
	else
		utils->lexer_root = new_node;
	return (new_node);
}

t_ast_utils	*ft_utils_init(void)
{
	t_ast_utils	*utils;

	utils = malloc(sizeof(t_ast_utils));
	if (!utils)
		return (NULL);
	utils->lexer_root = NULL;
	utils->parser_root = NULL;
	utils->env_root = NULL;
	return (utils);
}

bool	ft_check_last_node(t_ast_utils *utils)
{
	t_lexer	*lx_node;

	lx_node = utils ->lexer_root;
	while (lx_node->next)
		lx_node = lx_node->next;
	if (lx_node->token == GREAT || lx_node->token == GREAT_GREAT)
		return (true);
	if (lx_node->token == LESS || lx_node->token == LESS_LESS)
		return (true);
	return (false);
}
