/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 17:51:19 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/27 13:56:46 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_lexer	*new_lexer_node(char **content, int token, int i, t_ast_utils *utils)
{
	t_lexer	*new_node;

	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		return (NULL);
	new_node->content = content[i];
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

int	ft_token_type(char **str, t_ast_utils *utils, int i)
{
	static bool	cmd;
	static bool	redir;

	if (i == 0)
	{
		redir = false;
		cmd = false;
	}
	if (ft_strncmp(str[i], "|\0", 2) == 0)
	{
		cmd = false;
		utils->pipes++;
		return (PIPE);
	}
	if (ft_strncmp(str[i], ">\0", 2) == 0)
	{
		redir = true;
		return (GREAT);
	}
	if (ft_strncmp(str[i], ">>\0", 3) == 0)
	{
		redir = true;
		return (GREAT_GREAT);
	}
	if (ft_strncmp(str[i], "<\0", 2) == 0)
	{
		redir = true;
		return (LESS);
	}
	if (ft_strncmp(str[i], "<<\0", 3) == 0)
	{
		redir = true;
		return (LESS_LESS);
	}
	else if (!cmd)
	{
		cmd = true;
		return (CMD);
	}
	else if (redir == true)
		return (REDIR_FILE);
	else
		return (ARG);
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
	ft_printf("LEXER NODES:\n");
	ft_printf("El numero de pipes es: %i\n", tmp->utils->pipes);
	while (tmp)
	{
		ft_printf("\nNODO: %i\n", tmp->i);
		ft_printf("CONT: %s\n", tmp->content);
		ft_printf("TOKEN: %i\n", tmp->token);
		ft_printf("\n");
		tmp = tmp->next;
	}
}

t_lexer	*ft_lexer(char **cmdsplit)
{
	int			i;
	t_ast_utils	*utils;
	t_lexer		*tmp_node;

	i = 0;
	utils = ft_utils_init();
	while (cmdsplit[i])
	{
		tmp_node = new_lexer_node(cmdsplit,
				ft_token_type(cmdsplit, utils, i), i, utils);
		if (i == 0)
			tmp_node->utils->lexer_root = tmp_node;
		else
			ft_lxadd_back(&tmp_node->utils->lexer_root, tmp_node);
		i++;
	}
	ft_printlx(utils->lexer_root);
	return (utils->lexer_root);
}
