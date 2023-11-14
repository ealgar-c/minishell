/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ealgar-c <ealgar-c@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/14 13:45:53 by ealgar-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_echo(t_parser *parser_node, t_info *info)
{
	int		i;

	i = 1;
	if (!parser_node->cmd[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(parser_node->cmd[i], "-n ") == 0
		|| ft_strcmp(parser_node->cmd[i], "-n") == 0)
		i++;
	while (parser_node->cmd[i])
	{
		if (!parser_node->cmd[i + 1])
			ft_printf("%s", parser_node->cmd[i]);
		else
			ft_printf("%s ", parser_node->cmd[i]);
		i++;
	}
	if (ft_strcmp(parser_node->cmd[1], "-n " ) != 0
		&& ft_strcmp(parser_node->cmd[1], "-n") != 0)
		ft_printf("\n");
	info->exit_status = 0;
}
