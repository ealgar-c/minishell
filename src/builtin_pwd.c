/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 15:55:45 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/10/02 18:48:31 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_pwd_exec(t_info *info)
{
	char	*path;

	path = malloc(sizeof(char) * 100);
	path = getcwd(path, 100);
	ft_printf("%s\n", path);
	free(path);
	info->last_exit = 1;
}

void	ft_pwd(t_parser *parser_node, t_info *info)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == -1)
		exit (0);
	else if (pid == 0)
	{
		ft_redirector(parser_node);
		ft_pwd_exec(info);
		exit(0);
	}
	else
		waitpid(-1, &status, 0);
	return ;
}
