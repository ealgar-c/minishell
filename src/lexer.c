/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:51:19 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/22 18:01:43 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*new_lexer_node(char *content, int token, int i, t_ast_utils *utils)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->content = content;
	new_node->i = i;
	new_node->token = token;
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->utils = utils;
	return (new_node);
}

void	ft_lxadd_back(t_lexer **root, t_lexer *new)
{
	t_lexer	*ptr;

	ptr = *root;
	while (ptr->next)
		ptr = ptr->next;
	ptr->next = new;
	ptr->next->prev = ptr;
}

int	ft_token_type(char *str, t_ast_utils *utils, int i) // esto esta antiguo, no pone args
{
	static	bool cmd;

	if (i == 0)
		cmd = false;
	if (ft_strncmp(str, "|", 1) == 0)
	{
		cmd = false;
		utils->pipes++;
		return (PIPE);
	}
	if (ft_strncmp(str, ">", 1) == 0)
		return (GREAT);
	if (ft_strncmp(str, ">>", 2) == 0)
		return (GREAT_GREAT);
	if (ft_strncmp(str, "<", 1) == 0)
		return (LESS);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (LESS_LESS);
	else if (!cmd)
	{
		cmd = true;
		return (CMD);
	}
	else
	{
		return (ARG);
	}
}

t_ast_utils	*ft_utils_init(void)
{
	t_ast_utils	*utils;

	utils = malloc(sizeof(t_ast_utils));
	if (!utils)
		return (NULL);
	utils->pipes = 0;
	utils->lexer_len = 0;
	return (utils);
}

void	ft_printlx(t_lexer *root)
{
	t_lexer	*tmp;

	tmp = root;
	while (tmp)
	{
		printf("\nNODO: %i\n", tmp->i);
		printf("CONT: %s\n", tmp->content);
		printf("TOKEN: %i\n", tmp->token);
		printf("\n");
		tmp = tmp->next;
	}
}

void	ft_lexer(char **cmdsplit)
{
	int			i;
	t_ast_utils	*utils;
	t_lexer		*tmp_node;

	i = 0;
	utils = ft_utils_init();
	while (cmdsplit[i])
	{
		printf("cmds[%d]: %s\n", i, cmdsplit[i]);
		i++;
	}
	i = 0;
	while (cmdsplit[i])
	{
		tmp_node = new_lexer_node(cmdsplit[i], ft_token_type(cmdsplit[i], utils, i), i, utils);
		printf("todo = %s\n", tmp_node->content);
		if (i == 0)
			tmp_node->utils->lexer_root = tmp_node;	
		else
			ft_lxadd_back(&tmp_node->utils->lexer_root, tmp_node);
		i++;
	}
	ft_printlx(utils->lexer_root);
}
