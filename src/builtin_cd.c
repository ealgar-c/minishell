/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 17:13:34 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/09/30 18:51:58 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_cd(t_parser *parser_node, t_info *info)
{
	int		i;
	char	*path;
	char	**cmd;

	cmd = ft_split(parser_node->cmd, ' ');
	i = 1;
	if (!cmd[1])
		path = getenv("HOME");
	else
	{
		path = cmd[i];
		while (cmd[++i])
			path = ft_strjoin(ft_strjoin(path, " "), cmd[i]);
	}
	if (chdir((const char *)(path)) == -1)
	{
		ft_printf("cd: %s: No such file or directory\n", path);
		info->last_exit = 1;
	}
	else
		info->last_exit = 0;
}
