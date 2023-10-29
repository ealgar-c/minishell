/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:37:46 by erivero-          #+#    #+#             */
/*   Updated: 2023/10/29 12:46:23 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ctrlc_handler(int sig)
{
	(void)sig;
	if (!g_signals.builtin && !g_signals.heredoc)
	{
		ft_printf("\033[0;34mholi modo ehpesia\n \033[0m");
		write(1, "\033[K\n", 5);
		rl_replace_line("", 0);
		g_signals.builtin = true;
	}
	else if (g_signals.heredoc)
	{
		write(1, "\033[K\n", 5);
		close(0);
		g_signals.heredoc = false;
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
		write(1, "\033[K\n", 5);
		rl_on_new_line();
		rl_redisplay();
		rl_replace_line("", 0);
	}
}
