/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/19 15:05:26 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

void	ft_exit(char **cmd, t_info *info)
{
	int	exit_arg;

	exit_arg = 0;
	ft_printf("exit\n");
	if (cmd[1])
	{
		if (ft_isalpha(cmd[1][0]))
			ft_printf("exit: numeric argument required\n");
		else
			exit_arg = ft_atoi(cmd[1]);
	}
	ft_free_utils(info, true);
	free(info);
	atexit(ft_leakss);
	rl_clear_history();
	exit (exit_arg);
}
