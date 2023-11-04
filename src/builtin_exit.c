/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/04 12:30:42 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

/* void	ft_exit_heredoc(t_info *info)
{
	t_parser	*ptr;

	ptr = info->utils->parser_root;
	if (!ptr)
		return ;
	while (ptr)
	{
		if (ptr->heredoc_flag)
		{
			ft_heredoc(ptr, info);
		}
		ptr = ptr->next;
	}
} */

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
