/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_arguments_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 12:13:15 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/19 15:06:18 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_copyarg(char *dest, char *orig)
{
	int	i;

	i = 0;
	while (orig[i])
	{
		dest[i] = orig[i];
		i++;
	}
	dest[i] = '\0';
}

void	get_final_cmd(t_parser *node)
{
	int				i;
	t_parser_args	*tmp;

	i = 1;
	tmp = node->tmp_arg;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	node->cmd = malloc(sizeof(char *) * i);
	i = 0;
	tmp = node->tmp_arg;
	while (tmp)
	{
		node->cmd[i] = malloc(sizeof(char) * ft_strlen(tmp->str) + 1);
		ft_copyarg(node->cmd[i], tmp->str);
		tmp = tmp->next;
		i++;
	}
	node->cmd[i] = NULL;
}

t_parser_args	*par_newargnode(char *content)
{
	t_parser_args	*new_node;

	new_node = malloc(sizeof(t_parser_args));
	if (!new_node)
		return (NULL);
	new_node->str = content;
	new_node->next = NULL;
	return (new_node);
}

static t_parser_args	*lxargs_getactual(t_parser *root)
{
	t_parser		*p_tmp;
	t_parser_args	*args_tmp;

	p_tmp = root;
	while (p_tmp->next)
		p_tmp = p_tmp->next;
	args_tmp = p_tmp->tmp_arg;
	while (args_tmp->next)
		args_tmp = args_tmp->next;
	return (args_tmp);
}

void	get_arguments(t_lexer *lex, t_parser *par)
{
	t_parser_args	*tmp;

	tmp = lxargs_getactual(par);
	tmp->next = par_newargnode(lex->content);
}
