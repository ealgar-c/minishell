/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:57:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/14 13:23:28 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_env_exec(t_info *info)
{
	t_env	*tmp;

	tmp = info->env_root;
	while (tmp)
	{
		if (tmp->value[0])
			ft_printf("%s=%s\n", tmp->name, tmp->value);
		tmp = tmp->next;
	}
}

void	ft_env(t_parser *parser_node, t_info *info)
{
	if (parser_node->cmd[1])
	{
		ft_printf("\033[0;33mconchita: env: \033[0m\n");
		ft_printf("\033[0;33mNo arguments supported\n\033[0m\n");
		info->exit_status = 1;
		return ;
	}
	ft_env_exec(info);
	info->exit_status = 0;
}
