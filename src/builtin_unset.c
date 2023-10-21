/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 12:13:02 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/21 11:59:25 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//esto es provisional pq hasta que no se arregle export está sujeto a cambios

static void del_variable(t_env	*node)
{
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

	i = 1;
	ft_printf("la variable a borrar es: %s\n", parser_node->cmd[i]);
	if (!parser_node->cmd[i])
		return ;
	while (parser_node->cmd[i])
	{
		ft_printf("iteración número: %i\n", i);
		ptr = info->env_root;
		if (!ptr)
			return ;
		ft_printf("el puntero ha sido creado\n");
		while(ptr)
		{
			if (!ft_strcmp(parser_node->cmd[i], ptr->name))
			{
				del_variable(ptr);
				break ;
			}
			ptr = ptr->next;
		}
		i++;
	}
}