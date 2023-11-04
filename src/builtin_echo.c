/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erivero- <erivero-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 11:24:18 by ealgar-c          #+#    #+#             */
/*   Updated: 2023/11/04 17:08:42 by erivero-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* char	*clean_quotes(char *content)
{
	return (ft_strtrim(content, "\"\'"));
} */

void	ft_echo(t_parser *parser_node, t_info *info)
{
	int		i;

	i = 1;
	if (!parser_node->cmd[i])
	{
		write(1, "\n", 1);
		return ;
	}
	if (ft_strcmp(parser_node->cmd[i], "-n ") == 0)
		i++;
	while (parser_node->cmd[i])
	{
		ft_printf("%s", parser_node->cmd[i]);
		i++;
	}
	if (ft_strcmp(parser_node->cmd[1], "-n " ) != 0)
		ft_printf("\n");
	info->exit_status = 0;
}
