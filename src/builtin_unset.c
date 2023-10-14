/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/14 12:32:04 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//esto es provisional pq hasta que no se arregle export está sujeto a cambios
//sería conveniente enlazar la lista con el previo
void del_variable(t_env	*node)
{
	node->prev->next = node->next;
	node->next->prev = node->prev;
	free(node->name);
	free(node->value);
	free(node->next);
	free(node->prev);
	free(node);
}

void ft_unset(t_parser *parser_node, t_info *info)
{
	char **name;
	t_env	*ptr;
	int		i;

	i = 1;
	name = ft_split(parser_node->cmd, 32);
	while (name[i])
	{
		ptr = info->env_root;
		while(ptr)
		{
			if (!ft_strncmp(name[i], ptr->name, ft_strlen(name[i])))
			{
				del_variable(ptr);
				break ;
			}
			ptr = ptr->next;
		}
		i++;
	}
	ft_free(name);
}