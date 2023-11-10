/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/10 13:52:46 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

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
	if (i != 1)
		return (false);
	return (true);
}

static int	get_first_arg(char **cmd)
{
	if (ft_isalpha(cmd[1][0]))
	{
		ft_printf("exit: numeric argument required\n");
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
	ft_printf("exit\n");
	if (cmd[1])
		exit_arg = get_first_arg(cmd);
	if (cmd[2])
	{
		if (exit_arg != 255 && exit_arg != 0)
		{
			ft_printf("exit: too many arguments\n");
			return ;
		}
	}
	ft_free_utils(info, true);
	free(info);
	atexit(ft_leakss);
	rl_clear_history();
	exit (exit_arg);
}
