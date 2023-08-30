/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:08:12 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/30 12:27:29 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_exit(char **cmd)
{
	if (cmd[1])
		ft_printf("Flags no suported in this case\n");
//	ft_free(whatever);
	exit (0);
}

//con previa revisión de pipes y split 
// el primer string de cmd sería el comando y lo siguiente las flags
void	ft_filter(char **cmd)
{
	if ((ft_strncmp(cmd[0], "echo", 4) == 0))
		ft_echo(cmd);
	if ((ft_strncmp(cmd[0], "cd", 2) == 0))
		ft_cd(cmd);
	if ((ft_strncmp(cmd[0], "pwd", 3) == 0))
		ft_pwd(cmd);
	if ((ft_strncmp(cmd[0], "export", 6) == 0))
		ft_export(cmd);
	if ((ft_strncmp(cmd[0], "unset", 5) == 0))
		ft_unset(cmd);
	if ((ft_strncmp(cmd[0], "env", 3) == 0))
		ft_env(cmd);
	if ((ft_strncmp(cmd[0], "exit", 4) == 0))
		ft_exit(cmd);
/* 	else
		 cositas con execve que no vienen al caso */
}
