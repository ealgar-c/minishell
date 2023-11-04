/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/11/04 12:41:04 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//esto es provisional pq hasta que no se arregle export está sujeto a cambios

static void	del_variable(t_env	*node)
{
//	ft_printf("la variable a borrar es: %s\n", node->name);
	if (node->prev)
		node->prev->next = node->next;
	if (node->next)
		node->next->prev = node->prev;
	free(node->name);
	free(node->value);
	free(node);
}

void ft_unset(t_parser *parser_node, t_info *info)
{
	t_env	*ptr;
	int		i;
	char	*name;

	i = 0;
	if (!parser_node->cmd[i])
		return ;
	info->exit_status = 0;
	while (parser_node->cmd[++i])
	{
		name = ft_strtrim(parser_node->cmd[i], " ");
		ptr = info->env_root;
		if (!ptr)
			return ;
		while (ptr)
		{
			if (!ft_strcmp(name, ptr->name))
			{
				del_variable(ptr);
				break ;
			}
			else
				info->exit_status = 1;
			ptr = ptr->next;
		}
		free(name);
	}
}
