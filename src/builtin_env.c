/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:57:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/04 17:08:54 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_env_exec(t_info *info)
{
	t_env	*tmp;

	tmp = info->env_root;
	while (tmp)
	{
		ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_env(t_parser *parser_node, t_info *info)
{
	if (parser_node->cmd[1])
	{
		ft_printf("No arguments supported\n");
		info->exit_status = 1;
		return ;
	}
	ft_env_exec(info);
	info->exit_status = 0;
}
