/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 00:57:30 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/09 01:00:41 by ealgar-c         ###   ########.fr       */
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
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (0);
	else if (pid == 0)
	{
		ft_redirector(parser_node);
		ft_env_exec(info);
		exit(0);
	}
	else
		waitpid(-1, &status, 0);
	return ;
}
