/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/14 13:23:28 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* void	ft_leakss(void)
{
	system("leaks -q minishell");
	atexit(ft_leakss);
}
 */

static	bool	only_arg(t_info *info)
{
	int			i;
	t_parser	*tmp;

	i = 0;
	tmp = info->utils->parser_root;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	if (i > 1)
		return (false);
	return (true);
}

static int	get_first_arg(char **cmd)
{
	if (ft_isalpha(cmd[1][0]))
	{
		ft_printf("\033[0;33mconchita: exit: %s: \033[0m", cmd[1]);
		ft_printf("\033[0;33mnumeric argument required\n\033[0m");
		return (255);
	}
	else
		return (ft_atoi(cmd[1]));
}

void	ft_exit(char **cmd, t_info *info)
{
	int	exit_arg;

	if (!only_arg(info))
		return ;
	exit_arg = 0;
	if (!info->exit_status)
		ft_printf("\033[0;32mexit\n\033[0m");
	else
		ft_printf("\033[0;31mexit\n\033[0m");
	if (cmd[1])
		exit_arg = get_first_arg(cmd);
	if (cmd[2])
	{
		if (exit_arg != 255 && exit_arg != 0)
		{
			ft_printf("\033[0;33mconchita: exit: too many arguments\n\033[0m");
			return ;
		}
	}
	ft_free_utils(info, true);
	free(info);
	rl_clear_history();
	exit (exit_arg);
}
