/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:08:12 by erivero-          #+#    #+#             */
/*   Updated: 2023/08/30 13:24:06 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


//con previa revisión de pipes y split 
// el primer string de cmd sería el comando y lo siguiente las flags
void	ft_filter(char **cmd, char **envp)
{
	if ((ft_strncmp(cmd[0], "echo", 4) == 0))
		ft_echo(cmd);
	else if ((ft_strncmp(cmd[0], "cd", 2) == 0))
		ft_cd(cmd);
	else if ((ft_strncmp(cmd[0], "pwd", 3) == 0))
		ft_pwd(cmd);
	else if ((ft_strncmp(cmd[0], "export", 6) == 0))
		ft_export(cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0))
		ft_unset(cmd);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0))
		ft_env(cmd);
	else if ((ft_strncmp(cmd[0], "exit", 4) == 0))
		ft_exit(cmd);
	else
		executer(cmd, envp);
}
