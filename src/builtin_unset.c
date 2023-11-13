/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/13 18:32:44 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	del_variable(t_env	*node)
{
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->name);
	free(node->value);
	free(node);
}

static void	ft_eraser(char	*name, t_env *ptr)
{
	while (ptr)
	{
		if (!ft_strcmp(name, ptr->name))
		{
			del_variable(ptr);
			break ;
		}
/* 		else en bash no se setea a 1 si intento borrar algo que no existe
			info->exit_status = 1; */
		ptr = ptr->next;
	}
}

void	ft_unset(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	int		i;
//	char	*name;

	i = 0;
	if (!parser_node->cmd[i])
		return ;
	info->exit_status = 0;
	while (parser_node->cmd[++i])
	{
//		name = ft_strtrim(parser_node->cmd[i], " "); // este trim estaría bien quitarlo
		ptr = info->env_root;
		if (!ptr)
			return ;
		if (input_checker(parser_node->cmd[i], parser_node->cmd[0]))
			ft_eraser(parser_node->cmd[i], ptr);
		else
			info->exit_status = 1;
	}
}
