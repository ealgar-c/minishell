/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 12:08:12 by erivero-          #+#    #+#             */
/*   Updated: 2023/09/29 13:00:26 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


//con previa revisión de pipes y split 
// el primer string de cmd sería el comando y lo siguiente las flags
bool	ft_filter(t_parser *parser_node, char **cmd)
{
	if ((ft_strncmp(cmd[0], "echo\0", 5) == 0))
		ft_echo(parser_node);
	else if ((ft_strncmp(cmd[0], "cd\0", 3) == 0))
		ft_cd(cmd);
	else if ((ft_strncmp(cmd[0], "pwd\0", 4) == 0))
		ft_pwd(cmd);
	/* else if ((ft_strncmp(cmd[0], "export", 6) == 0))
		ft_export(cmd);
	else if ((ft_strncmp(cmd[0], "unset", 5) == 0))
		ft_unset(cmd);
	else if ((ft_strncmp(cmd[0], "env", 3) == 0))
		ft_env(cmd); */
	else if ((ft_strncmp(cmd[0], "exit\0", 5) == 0))
		ft_exit(cmd);
	else
		return (false);
	return (true);		
}
