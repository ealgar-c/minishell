/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:40:32 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/09 18:04:01 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_leakss(void)
{
	system("leaks -q minishell");
}

void	ft_exit(char **cmd, t_info *info)
{
	if (cmd[1]) //realmente no, si es un numero es lo que tenemos que usar en exit
		ft_printf("exit: numeric argument required\n");
	ft_free_utils(info, true);
	free(info);
	ft_printf("exit\n");
	atexit(ft_leakss);
	exit (0);
}
